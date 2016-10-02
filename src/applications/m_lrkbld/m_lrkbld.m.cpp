// m_lrkbld.m.cpp                                                     -*-C++-*-

// @PURPOSE: Provide a build toolchain for the Lark Compiler.
//
// @DESCRIPTION: This component provides a program for building c++ projects
//  using the Lark Project Structure.

// LARK HEADERS
#include <m_lrkbld_cursor.h>

// C STANDARD LIBRARY HEADERS
#include <cassert>
#include <cstddef>
#include <cstdint>

// C++ STANDARD LIBRARY HEADERS
#include <deque>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

// POSIX HEADERS
#include <dirent.h>

// LINUX HEADERS
#include <linux/inotify.h>

namespace LarkCompiler {
namespace m_lrkbld {

// ============================================================================
//                          STATIC DECLARATIONS
// ============================================================================

// Aliases for primitive types
using Byte      = unsigned char;
using Boolean   = bool;
using Character = char;
using Integer   = int;
using Natural   = unsigned int;

constexpr Boolean True  = true;
constexpr Boolean False = false;

// Aliases for
using ErrorCode = Integer;

                        // =======================
                        // class LexicalComparison
                        // =======================

template <typename OBJECT>
struct LexicalComparison {

    // TYPES
    using Object = OBJECT;

    // ACCESSORS
    Boolean operator()(const Object& lhs,
                       const Object& rhs);
};

template <typename ENTITY>
Boolean LexicalComparison<ENTITY>::operator()(const ENTITY& lhs,
                                              const ENTITY& rhs)
{
    return lhs.lexicallyLess(rhs);
}

                        // ================
                        // class LexicalSet
                        // ================

template <typename ELEMENT>
using LexicalSet = std::set<ELEMENT, LexicalComparison<ELEMENT>>;

                        // ====================
                        // class DirectoryEntry
                        // ====================


class DirectoryEntry final {
    // This value-semantic class..

  private:
    // DATA
    std::string d_name;

  public:
    // CREATORS
    DirectoryEntry(const std::string& name);

    // ACCESSORS
    const std::string& name() const;

    // ASPECTS
    Boolean lexicallyLess(const DirectoryEntry& other) const;
};

                        // ===================
                        // class DirectoryUtil
                        // ===================

struct DirectoryUtil final {
    // This 'struct' provides a namespace for utility functions operating on
    // directories.

    // CLASS METHODS
    static ErrorCode getEntries(Cursor<DirectoryEntry> *output,
                                const std::string&      directoryName);

    static ErrorCode getEntries(std::vector<DirectoryEntry> *entries,
                                const std::string&           directoryName);
        // ..

    template <typename OUTPUT_ITERATOR>
    static ErrorCode getEntries(OUTPUT_ITERATOR    iterator,
                                const std::string& directoryName);
        // ..

};

                        // =========================
                        // class CompilationDatabase
                        // =========================

// TODO(nate): make variadic table class

template <typename ROW_TYPE>
class VirtualCursor {
    // This protocol class..

  public:
    // TYPES
    using RowType = ROW_TYPE;

  public:
    // CREATORS
    virtual ~VirtualCursor() = 0;

    // MANIPULATORS
    virtual void advance();

    // ACCESSORS
    virtual void element(RowType *output) const;

    virtual Boolean isAtEnd() const;
};

template <typename ROW_TYPE>
class DatabaseCursor {
    // This class..

  public:
    // TYPES
    using RowType = ROW_TYPE;
    using Impl    = VirtualCursor<RowType>;

  private:
    // DATA
    std::unique_ptr<Impl> d_impl_p;

  public:
    // CREATORS
    DatabaseCursor();

    // MANIPULATORS
    void reset(std::unique_ptr<Impl>&& d_impl_p);

    void advance();

    // ACCESSORS
    void element(RowType* output) const;

    Boolean isAtEnd() const;
};

class CompilationDatabase {
    // This class..

  public:
    // TYPES
    template <typename COLUMN_TYPE>
    using Column = std::deque<COLUMN_TYPE>;

    template <typename COLUMN_TYPE>
    using Index  = std::map<COLUMN_TYPE, Integer>;

    struct FileView {
        const std::string& name;
        Boolean            dirty;
    };

    struct EdgeView {
        const std::string& incoming;
        const std::string& outgoing;
    };

  private:
    // DATA
    // Files table
    Column<std::string> d_name;
    Column<Boolean>     d_dirty;
    Index<std::string>  d_nameIndex;

    // File dependencies table
    Column<std::string> d_incomingDependency;
    Column<std::string> d_outgoingDependency;
    Index<std::string>  d_incomingDependencyIndex;
    Index<std::string>  d_outgoingDependencyIndex;

  public:
    // CREATORS
    CompilationDatabase();

    // MANIPULATORS
    ErrorCode addFile(const std::string& name,
                      Boolean            dirty);
        // O(log n)

    ErrorCode deleteFile(const std::string& name);
        // O(log n)

    ErrorCode invalidateFile(const std::string& name);
        // Invalidate all files that depend on the specified 'fileName'.

    ErrorCode addDependency(const std::string& outgoingName,
                            const std::string& incomingName);

    ErrorCode deleteDependency(const std::string& outgoingName,
                               const std::string& incomingName);

    // ACCESSORS
    void getFile(DatabaseCursor<FileView> *output,
                 const std::string&        fileName) const;
        // O(log n)

    void getFileDependencies(DatabaseCursor<FileView> *output,
                             const std::string&        fileName) const;
        // O(log n + d)
        // where d is the number of dependencies of the file

    void getFileDependents(DatabaseCursor<FileView> *output,
                           const std::string&        fileName) const;
        // O(log n + d)
};

// ============================================================================
//                           STATIC DEFINITIONS
// ============================================================================

                        // --------------------
                        // class DirectoryEntry
                        // --------------------

// CREATORS
DirectoryEntry::DirectoryEntry(const std::string& name)
    : d_name(name)
{
}

// ACCESSORS
const std::string& DirectoryEntry::name() const
{
    return d_name;
}

// ASPECTS
Boolean DirectoryEntry::lexicallyLess(const DirectoryEntry& other) const
{
    return name() < other.name();
}

                        // -------------------
                        // class DirectoryUtil
                        // -------------------

// CLASS METHODS
ErrorCode DirectoryUtil::getEntries(std::vector<DirectoryEntry> *entries,
                                    const std::string&           directoryName)
{
    assert(entries);
    return getEntries(std::back_inserter(*entries), directoryName);
}

template <typename OUTPUT_ITERATOR>
ErrorCode DirectoryUtil::getEntries(OUTPUT_ITERATOR    iterator,
                                    const std::string& directoryName)
{
    DIR *stream = opendir(directoryName.c_str());
    for (dirent *entry  = readdir(stream);
                 entry != nullptr;
                 entry  = readdir(stream)) {
        *iterator++ = DirectoryEntry(entry->d_name);
    }
    closedir(stream);
    return 0;
}

}; // close package namespace
}; // close product namespace

// ============================================================================
//                                  MAIN
// ============================================================================

int main()
{
    // get a list of all of the directories in the current directory,
    // walk through source, and recursively through the packages
    using namespace LarkCompiler::m_lrkbld;
    ErrorCode rc = 0;

    LexicalSet<DirectoryEntry> entries;
    rc = DirectoryUtil::getEntries(std::inserter(entries, entries.begin()),
                                   ".");
    if (0 != rc) {
        return rc;
    }
    for (const DirectoryEntry& entry : entries) {
        std::cout << entry.name()
                  << "\n"
                  << std::flush;
    }

    return rc;
}
