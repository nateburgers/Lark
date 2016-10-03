// m_lrkbld_filesystem.h
#ifndef INCLUDED_M_LRKBLD_FILESYSTEM
#define INCLUDED_M_LRKBLD_FILESYSTEM

// LARK HEADERS
#ifndef INCLUDED_M_LRKBLD_CURSOR
#include <m_lrkbld_cursor.h>
#endif

// STANDARD LIBRARY HEADERS
#ifndef INCLUDED_STRING
#include <string>
#define INCLUDED_STRING
#endif

// POSIX HEADERS
#ifndef INCLUDED_DIRENT
#include <dirent.h>
#define INCLUDED_DIRENT
#endif

#ifndef INCLUDED_SYS_TYPES
#include <sys/types.h>
#define INCLDUED_SYS_TYPES
#endif

namespace LarkCompiler {
namespace m_lrkbld {

using ErrorCode = int;

class DirectoryEntry {
    // This value-semantic class..

  public:
    // TYPES
    using IdType = ino_t;

  private:
    // DATA
    std::string d_name;
    IdType      d_id;

  public:
    // CREATORS
    DirectoryEntry() = default;

    DirectoryEntry(const std::string&  name,
                   IdType              id);

    DirectoryEntry(std::string&& name,
                   IdType        id);

    DirectoryEntry(const DirectoryEntry&  source) = default;
    DirectoryEntry(      DirectoryEntry&& source) = default;

   ~DirectoryEntry() = default;
    
    // MANIPULATORS
    DirectoryEntry& operator=(const DirectoryEntry&  source) = default;
    DirectoryEntry& operator=(      DirectoryEntry&& source) = default;

    std::string& name();

    IdType& id();
    
    // ACCESSORS
    const std::string& name() const;

    const IdType& id() const;
};

class VirtualFileSystem {
    // This protocol class..

  public:
    // CREATORS
    virtual ~VirtualFileSystem() = default;

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

                        // ==========================
                        // class DirectoryEntryCursor
                        // ==========================

class DirectoryEntryCursor : public VirtualCursor<DirectoryEntry> { 
    // This mechanism..
    
  public:
    // TYPES

  private:
    // DATA
    DIR    *d_stream_p;
    dirent *d_entry_p;

  public:
    // CREATORS
    DirectoryEntryCursor() = delete;

    DirectoryEntryCursor(DIR *stream);

    DirectoryEntryCursor(const DirectoryEntryCursor&  source) = delete;
    DirectoryEntryCursor(      DirectoryEntryCursor&& source) = default;

    virtual ~DirectoryEntryCursor();

    // MANIPULATORS
    DirectoryEntryCursor& operator=(
                                  const DirectoryEntryCursor& source) = delete;
    DirectoryEntryCursor& operator=(DirectoryEntryCursor&& source)   = default;

    virtual void advance();

    // ACCESSORS
    virtual void element(DirectoryEntry *output) const;

    virtual bool done() const;
};

// ============================================================================
//                            INLINE DEFINITIONS
// ============================================================================

                        // --------------------------
                        // class DirectoryEntryCursor
                        // --------------------------
                         
// CREATORS
DirectoryEntryCursor::DirectoryEntryCursor(DIR *stream)
    : d_stream_p(stream)
    , d_entry_p(readdir(stream))
{
}

DirectoryEntryCursor::~DirectoryEntryCursor()
{
    closedir(d_stream_p);
}

// MANIPULATORS
void DirectoryEntryCursor::advance()
{
    d_entry_p = readdir(d_stream_p);
}

// ACCESSORS
void DirectoryEntryCursor::element(DirectoryEntry *output) const
{
    *output = DirectoryEntry(d_entry_p->d_name,
                             d_entry_p->d_ino);
}

bool DirectoryEntryCursor::done() const
{
    return nullptr == d_entry_p;
}

} // close package namespace
} // close product namespace

// ----------------------------------------------------------------------------
// Copyright 2016 Nathan Burgers
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at 
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed in writing, software 
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ----------------------------------------------------------------------------

#endif // INCLUDED_M_LRKBLD_FILESYSTEM
