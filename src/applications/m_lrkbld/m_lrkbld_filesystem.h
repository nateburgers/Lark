// m_lrkbld_filesystem.h
#ifndef INCLUDED_M_LRKBLD_FILESYSTEM
#define INCLUDED_M_LRKBLD_FILESYSTEM

#ifndef INCLUDED_M_LRKBLD_CURSOR
#include <m_lrkbld_cursor.h>
#endif

namespace LarkCompiler {
namespace m_lrkbld {

using ErrorCode = int;

class DirectoryEntry {
};

class VirtualFileSystem {
    // This protocol class..

  public:
    // CREATORS
    virtual ~VirtualFileSystem() = default;

    // MANIPULATORS
    virtual ErrorCode makeDirectory(const std::string& path) = 0;

    // ACCESSORS
    virtual ErrorCode getEntries(
                              Cursor<DirectoryEntry> *output,
                              const std::string&      directoryName) const = 0;

    virtual ErrorCode getEntries(Cursor<DirectoryEntry> *output) const = 0;
};

class FileSystem {
  private:
    // DATA 
    std::unique_ptr<VirtualFileSystem> d_impl;

  public:
    // CREATORS
    FileSystem() = default;

    // MANIPULATORS
    
    // ACCESSORS
    ErrorCode getEntries(Cursor<DirectoryEntry> *output,
                         const std::string&      directoryName) const;

    ErrorCode getEntries(Cursor<DirectoryEntry> *output) const;
};

struct FileSystemUtil {

    // CLASS ACCESSORS
    static ErrorCode getNativeFileSystem(FileSystem *output);
};

} // close package namespace
} // close product namespace

#endif // INCLUDED_M_LRKBLD_FILESYSTEM
