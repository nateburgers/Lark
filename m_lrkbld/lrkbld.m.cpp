// lrkbld.m.cpp                                                        -*-C++-*-

//@PURPOSE: 
//
//@CLASSES:
//
//@DESCRIPTION:
//

// Standard library dependencies 
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

// Posix dependencies
namespace posix {
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

using Directory      = DIR;
using DirectoryEntry = dirent;
using FileNumber     = ino_t;
using FileStatus     = struct stat;
} // close posix namespace

// ===========================================================================
//                                DECLARATIONS
// ===========================================================================

namespace {

                         // ===========================
                         // class Optional<OBJECT_TYPE>
                         // ===========================

template <typename OBJECT_TYPE>
class Optional {
    // This value semantic class provides a near standards-compliant 
    // implementation of 'std::optional' in C++11.

  public:
    // TYPES
    using Object = OBJECT_TYPE;

  private:
    // PRIVATE TYPES
    enum class Tag {
        e_IS_VALUE,
        e_IS_NULL,
    };

    union Data {
        struct { } d_null;
        Object     d_object;
    };

    // DATA
    Tag  d_tag;
    Data d_data;

  public:
    // CREATORS
    Optional();
    
    Optional(const Optional&  original);
    Optional(const Optional&& original);

    template <typename OTHER_OBJECT_TYPE>
    Optional(const Optional<OTHER_OBJECT_TYPE>& original);

    template <typename OTHER_OBJECT_TYPE>
    Optional(Optional<OTHER_OBJECT_TYPE>&& original);

    explicit Optional(const Object&  object);
    explicit Optional(      Object&& object);

    template <typename... OBJECT_CONSTRUCTOR_ARGUMENTS>
    explicit Optional(OBJECT_CONSTRUCTOR_ARGUMENTS&&... arguments);

    ~Optional();
    
    // MANIPULATORS
    Optional& operator=(const Optional&  original);
    Optional& operator=(      Optional&& original);

    template <typename OTHER_OBJECT_TYPE>
    Optional& operator=(const Optional<OTHER_OBJECT_TYPE>& original);

    template <typename OTHER_OBJECT_TYPE>
    Optional& operator=(Optional<OTHER_OBJECT_TYPE>&& original);

    Optional& operator=(const Object&  object);
    Optional& operator=(      Object&& object); 

    template <typename OTHER_OBJECT_TYPE>
    Optional& operator=(OTHER_OBJECT_TYPE&& object);

    Object& operator*();
    Object *operator->();

    Object& value();

    template <typename... OBJECT_CONSTRUCTOR_ARGUMENTS>
    void createInPlace(OBJECT_CONSTRUCTOR_ARGUMENTS&&... arguments);

    void swap(Optional& other);

    void reset();
    
    // ACCESSORS
    const Object& operator*() const;
    const Object *operator->() const;

    const Object& value() const;

    bool hasValue() const;

    explicit operator bool() const;
};

                      // ================================
                      // class VirtualCursor<OBJECT_TYPE>
                      // ================================

template <typename OBJECT_TYPE>
class VirtualCursor {

  public:
    // TYPES
    using Object = OBJECT_TYPE;

    // CREATORS
    virtual ~VirtualCursor() = 0; 
    
    // MANIPULATORS
    virtual VirtualCursor& operator++() = 0;

    virtual Object *operator->() = 0;

    virtual Object& operator*() = 0;
    
    // ACCESSORS
    virtual const Object *operator->() const = 0;

    virtual const Object& operator*() const = 0;

    virtual explicit operator bool() const = 0;

};

                          // =========================
                          // class Cursor<OBJECT_TYPE>
                          // =========================

template <typename OBJECT_TYPE>
class Cursor {

  public:
    // TYPES
    using Object        = OBJECT_TYPE;
    using VirtualCursor = VirtualCursor<Object>;
    
  private:
    // DATA
    std::unique_ptr<VirtualCursor> d_cursor_p;

  public:
    // CREATORS
    Cursor() = delete;

    explicit Cursor(std::unique_ptr<VirtualCursor>&& cursor);

    Cursor(const Cursor&  original) = delete;
    Cursor(      Cursor&& original) = default;

    ~Cursor() = default;
    
    // MANIPULATORS
    Cursor& operator=(const Cursor&  original) = delete;
    Cursor& operator=(      Cursor&& original) = default;

    Cursor& operator++();

    Object *operator->();

    Object& operator*();

    // ACCESSORS
    const Object *operator->() const;

    const Object& operator*() const;

    explicit operator bool() const;
};
                           
                            // ====================
                            // class DirectoryEntry
                            // ====================

class DirectoryEntry {

    // DATA
    std::string       d_name;
    posix::FileNumber d_fileNumber;

  public:
    // CREATORS
    DirectoryEntry() = default;

    DirectoryEntry(const std::string&       name,
                   const posix::FileNumber& fileNumber);

    DirectoryEntry(const DirectoryEntry&  original) = default;
    DirectoryEntry(      DirectoryEntry&& original) = default;

    ~DirectoryEntry() = default; 

    // MANIPULATORS
    DirectoryEntry& operator=(const DirectoryEntry&  original) = default;
    DirectoryEntry& operator=(      DirectoryEntry&& original) = default;
    
    void setName(const std::string& name);

    void setFileNumber(const posix::FileNumber& fileNumber);
    
    // ACCESSORS
    const std::string& name() const;

    const posix::FileNumber& fileNumber() const;
};
 

                               // ===============
                               // class Directory
                               // ===============

class Directory {

    // DATA
    posix::Directory *d_directory_p;

  public:
    // CREATORS
    Directory() = delete;

    explicit Directory(posix::Directory *directory);

    Directory(const Directory&  original) = delete;
    Directory(      Directory&& original) = default;

    ~Directory() = default;
    
    // MANIPULATORS
    Directory& operator=(const Directory&  original) = delete;
    Directory& operator=(      Directory&& original) = default;

    int close();

    Optional<DirectoryEntry> read();

    void rewind();
    
    void seek(long int steps);
};

                         // ==========================
                         // class DirectoryEntryCursor
                         // ==========================

class DirectoryEntryCursor : public VirtualCursor<DirectoryEntry> {

    // DATA
    Directory                d_directory;
    Optional<DirectoryEntry> d_directoryEntry;

  public:
    // CREATORS
    DirectoryEntryCursor() = delete;

    explicit DirectoryEntryCursor(Directory&& directory);

    DirectoryEntryCursor(const DirectoryEntryCursor&  original) = delete;
    DirectoryEntryCursor(      DirectoryEntryCursor&& original) = default;

    ~DirectoryEntryCursor() override;

    // MANIPULATORS
    DirectoryEntryCursor& operator++() override;

    DirectoryEntry *operator->() override;

    DirectoryEntry& operator*() override;

    // ACCESSORS
    const DirectoryEntry *operator->() const override;

    const DirectoryEntry& operator*() const override;

    explicit operator bool() const override;
};

                              // ================
                              // class FileStatus
                              // ================

class FileStatus {
};

                            // ====================
                            // struct DirectoryUtil
                            // ====================

struct DirectoryUtil {

    // CLASS METHODS
    static Directory open(const std::string& name);

    static Cursor<DirectoryEntry> list(const std::string& name);
};

struct DirectoryEntryUtil {
    static FileStatus stat(const DirectoryEntry& entry);
};

} // close unnamed namespace

// ============================================================================
//                                MAIN PROGRAM
// ============================================================================

int main(int numArguments, const char *arguments[])
{
    static_cast<void>(numArguments);
    static_cast<void>(arguments);

    for (Cursor<DirectoryEntry> fileCursor = DirectoryUtil::list(".");
                                fileCursor;
                              ++fileCursor) {
        const FileStatus stat = DirectoryEntryUtil::stat(*fileCursor);
        static_cast<void>(stat);
    }

    return 0;
}

// ============================================================================
//                               IMPLEMENTATION
// ============================================================================

namespace {
                            // --------------------
                            // class DirectoryEntry
                            // --------------------

// CREATORS
DirectoryEntry::DirectoryEntry(const std::string&       name,
                               const posix::FileNumber& fileNumber)
    : d_name(name)
    , d_fileNumber(fileNumber)
{
}

// MANIPULATORS
void DirectoryEntry::setName(const std::string& name)
{
    d_name = name;
}

void DirectoryEntry::setFileNumber(const posix::FileNumber& fileNumber)
{
    d_fileNumber = fileNumber;
}

// ACCESSORS
const std::string& DirectoryEntry::name() const
{
    return d_name;
}

const posix::FileNumber& DirectoryEntry::fileNumber() const
{
    return d_fileNumber;
}

                               // ---------------
                               // class Directory
                               // ---------------

// CREATORS
Directory::Directory(posix::Directory *directory)
    : d_directory_p(directory)
{
}

// MANIPULATORS
int Directory::close()
{
    return posix::closedir(d_directory_p);
}

Optional<DirectoryEntry> Directory::read()
{
    posix::DirectoryEntry *dirent = posix::readdir(d_directory_p);
    if (nullptr == dirent) {
        return Optional<DirectoryEntry>();
    }
    else {
        DirectoryEntry entry(dirent->d_name, dirent->d_ino);
        return Optional<DirectoryEntry>(std::move(entry));
    }
}

void Directory::rewind()
{
    posix::rewinddir(d_directory_p);
}

void Directory::seek(long int steps)
{
    posix::seekdir(d_directory_p, steps);
}

                             // -------------------
                             // class DirectoryUtil
                             // -------------------

// CLASS METHODS
Directory DirectoryUtil::open(const std::string& name)
{
    return Directory(posix::opendir(name.c_str()));
}

Cursor<DirectoryEntry> DirectoryUtil::list(const std::string& name)
{
    std::unique_ptr<DirectoryEntryCursor> cursor = 
                            std::make_unique<DirectoryEntryCursor>(open(name));
    return Cursor<DirectoryEntry>(std::move(cursor));
}

} // close unnamed namespace

// ============================================================================
//                                 UNIT TESTS
// ============================================================================

namespace {

} // close unnamed namespace
