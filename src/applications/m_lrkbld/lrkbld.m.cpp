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
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

// Posix dependencies
namespace posix {
extern "C" {
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

using Directory      = DIR;
using DirectoryEntry = dirent;
using FileNumber     = ino_t;
using FileMetadata   = struct stat;
} // close extern "C"
} // close posix namespace

// ===========================================================================
//                                DECLARATIONS
// ===========================================================================

namespace {

                                 // ==========
                                 // class Unit
                                 // ==========

class Unit {

  public:
    // CREATORS
    Unit() = default;

    Unit(const Unit&  original) = default;
    Unit(      Unit&& original) = default;

    ~Unit() = default;

    // MANIPULATORS
    Unit& operator=(const Unit&  original) = default;
    Unit& operator=(      Unit&& original) = default;
};

// FREE OPERATORS
bool operator==(const Unit& lhs, const Unit& rhs);

bool operator!=(const Unit& lhs, const Unit& rhs);

                      // ================================
                      // class Optional_Data<OBJECT_TYPE>
                      // ================================

template <typename OBJECT_TYPE>
union Optional_Data {

  public:
    // TYPES
    using Object = OBJECT_TYPE;

  private:
    // DATA
    Unit   d_null;
    Object d_object;

  public:
    // CREATORS
    Optional_Data();

    Optional_Data(const Object&  object);
    Optional_Data(      Object&& object);

    Optional_Data(const Optional_Data&  original) = delete;
    Optional_Data(      Optional_Data&& original) = delete;

    template <typename... OBJECT_CONSTRUCTOR_ARGUMENTS>
    Optional_Data(OBJECT_CONSTRUCTOR_ARGUMENTS&&... arguments);

    ~Optional_Data();

    // MANIPULATORS
    Optional_Data& operator=(const Optional_Data&  original) = delete;
    Optional_Data& operator=(      Optional_Data&& original) = delete;

    Object& object();

    void setObject(const Object&  object);
    void setObject(      Object&& object);

    template <typename... OBJECT_CONSTRUCTOR_ARGUMENTS>
    void createInPlace(OBJECT_CONSTRUCTOR_ARGUMENTS&&... arguments);

    void destroyObject();

    // ACCESSOR
    const Object& object() const;
};

                          // ========================
                          // struct Optional_DataUtil
                          // ========================

struct Optional_DataUtil {

    // CLASS METHODS
    template <typename LHS_OBJECT_TYPE, typename RHS_OBJECT_TYPE>
    static void copy(Optional_Data<LHS_OBJECT_TYPE>        *output,
                     const Optional_Data<RHS_OBJECT_TYPE>&  data,
                     bool                                   dataIsNull);

    template <typename LHS_OBJECT_TYPE, typename RHS_OBJECT_TYPE>
    static void move(Optional_Data<LHS_OBJECT_TYPE>   *output,
                     Optional_Data<RHS_OBJECT_TYPE>&&  data,
                     bool                              dataIsNull);
};

                             // ===================
                             // struct OptionalUtil
                             // ===================

struct OptionalUtil {

    // CLASS METHODS
    template <typename LHS_OBJECT_TYPE, typename RHS_OBJECT_TYPE>
    static void copy(Optional_Data<LHS_OBJECT_TYPE>        *output,
                     bool                                  *outputIsNull,
                     const Optional_Data<RHS_OBJECT_TYPE>&  data,
                     bool                                   dataIsNull);

    template <typename LHS_OBJECT_TYPE, typename RHS_OBJECT_TYPE>
    static void move(Optional_Data<LHS_OBJECT_TYPE>   *output,
                     bool                             *outputIsNull,
                     Optional_Data<RHS_OBJECT_TYPE>&&  data,
                     bool                              dataIsNull);
};

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
    using Data   = Optional_Data<Object>;

  private:
    // DATA
    bool d_isNull;
    Data d_data;

  public:
    // CREATORS
    Optional();

    Optional(const Optional&  original);
    Optional(      Optional&& original);

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

    bool isNull() const;

    explicit operator bool() const;
};

// FREE OPERATORS
template <typename LHS_OBJECT_TYPE, typename RHS_OBJECT_TYPE>
bool operator==(const Optional<LHS_OBJECT_TYPE>& lhs,
                const Optional<RHS_OBJECT_TYPE>& rhs);

template <typename LHS_OBJECT_TYPE, typename RHS_OBJECT_TYPE>
bool operator!=(const Optional<LHS_OBJECT_TYPE>& lhs,
                const Optional<RHS_OBJECT_TYPE>& rhs);

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
    using Object = OBJECT_TYPE;
    using Impl   = VirtualCursor<Object>;

  private:
    // DATA
    std::unique_ptr<Impl> d_cursor_p;

  public:
    // CREATORS
    Cursor() = delete;

    explicit Cursor(std::unique_ptr<Impl>&& cursor);

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

                               // ==============
                               // class FileType
                               // ==============

enum class FileType {
    e_BLOCK,
    e_CHARACTER,
    e_FIFO,
    e_REGULAR,
    e_DIRECTORY,
    e_SYMBOLIC_LINK,
    e_SOCKET,
};

                             // ==================
                             // class FileMetadata
                             // ==================

class FileMetadata {

    FileType d_type;

  public:
    // CREATORS
    FileMetadata() = delete;

    FileMetadata(const FileType& fileType);

    // MANIPULATORS
    // ACCESSORS
};

                           // =======================
                           // class VirtualFileSystem
                           // =======================

class VirtualFileSystem {

};

                            // ====================
                            // struct DirectoryUtil
                            // ====================

//struct DirectoryUtil {
//
//    // CLASS METHODS
//    static Directory open(const std::string& name);
//
//    static Cursor<DirectoryEntry> list(const std::string& name);
//};
//
//struct DirectoryEntryUtil {
//    static FileStatus stat(const DirectoryEntry& entry);
//};

                                 // ==========
                                 // class Path
                                 // ==========

class Path {

    // DATA
    std::vector<std::string> d_path;

  public:
    // CREATORS
    Path() = default;

    Path(const Path&  original) = default;
    Path(      Path&& original) = default;

    // MANIPULATORS
    Path& operator=(const Path&  original) = default;
    Path& operator=(      Path&& original) = default;

    void addChild(const std::string& directory);

    void addChild(const Path& path);

    void removeChild();

    void addParent(const std::string& directory);

    void addParent(const Path& path);

    // ACCESSORS
    Path child(const std::string& name) const;

    Path child(const Path& path) const;

    bool isRoot() const;

    Path parent() const;

    std::string string() const;

    std::string relativeString() const;

};

                           // =======================
                           // struct AbsolutePathUtil
                           // =======================

struct PathUtil  {

    // CLASS METHODS
    static Path parseRelative(const char path[]);

    static Path parseAbsolute(const char path[]);

    // CREATORS
    PathUtil() = delete;
};


} // close unnamed namespace

// ============================================================================
//                                MAIN PROGRAM
// ============================================================================

template <typename T> inline
static void unused(T&& object)
{
    static_cast<void>(object);
}

template <typename T, typename... Ts> inline
static void unused(T&& head, Ts&&... tail)
{
    unused(head);
    unused(tail...);
}

static int readPackage(std::ostream&          error,
                       std::set<std::string> *components,
                       posix::DIR            *directory,
                       const char             metadataDirectory[])
{
    unused(error, components, directory, metadataDirectory);

    for (posix::dirent *entry  = posix::readdir(directory);
                        entry != nullptr;
                        entry  = posix::readdir(directory)) {
    }
    return 0;
}

static int readPackages(std::ostream&          error,
                        std::set<std::string> *components,
                        posix::dirent         *directory,
                        const char             subdirectory[],
                        const char             metadataDirectory[])
{
    unused(error, components, directory, subdirectory, metadataDirectory);
    return 0;
}

static int readPackageGroups(std::ostream&          error,
                             std::set<std::string> *components,
                             posix::DIR            *directory)
{
    unused(error, components, directory);
    return 0;
}

int main(int argc, const char *argv[])
{
    unused(argc, argv);

    posix::DIR *directory = posix::opendir(".");
    if (nullptr == directory) {
        std::cerr << "Unable to open the current directory."
                  << std::flush;
        return -1;                                                    // RETURN
    }

    std::string           error;
    std::set<std::string> components;

    if (0 != readPackages(std::cerr, &components, directory, "applications",
                          "application")) {
        return -1;                                                    // RETURN
    }

    if (0 != readPackages(std::cerr, &components, directory, "adapters",
                          "package")) {
        return -1;                                                    // RETURN
    }

    if (0 != readPackages(std::cerr, &components, directory, "standalone",
                          "package")) {
        return -1;                                                    // RETURN
    }

    if (0 != readPackageGroups(std::cerr, &components, directory)) {
        return -1;                                                    // RETURN
    }

    return 0;
}

// ============================================================================
//                               IMPLEMENTATION
// ============================================================================

namespace {

                                 // ----------
                                 // class Unit
                                 // ----------

// FREE OPERATORS
inline
bool operator==(const Unit&, const Unit&)
{
    return true;
}

inline
bool operator!=(const Unit&, const Unit&)
{
    return false;
}

                      // --------------------------------
                      // class Optional_Data<OBJECT_TYPE>
                      // --------------------------------

// CREATORS
template <typename OBJECT_TYPE>
Optional_Data<OBJECT_TYPE>::Optional_Data()
    : d_null()
{
}

template <typename OBJECT_TYPE>
Optional_Data<OBJECT_TYPE>::Optional_Data(const Object& object)
    : d_object(object)
{
}

template <typename OBJECT_TYPE>
Optional_Data<OBJECT_TYPE>::Optional_Data(Object&& object)
    : d_object(std::move(object))
{
}


template <typename    OBJECT_TYPE>
template <typename... OBJECT_CONSTRUCTOR_ARGUMENTS>
Optional_Data<OBJECT_TYPE>::Optional_Data(
                                   OBJECT_CONSTRUCTOR_ARGUMENTS&&... arguments)
    : d_object(std::forward<OBJECT_CONSTRUCTOR_ARGUMENTS>(arguments)...)
{
}

template <typename OBJECT_TYPE>
Optional_Data<OBJECT_TYPE>::~Optional_Data()
{
}

// MANIPULATORS
template <typename OBJECT_TYPE>
OBJECT_TYPE& Optional_Data<OBJECT_TYPE>::object()
{
    return d_object;
}

template <typename OBJECT_TYPE>
void Optional_Data<OBJECT_TYPE>::setObject(const Object& object)
{
    d_object = object;
}

template <typename OBJECT_TYPE>
void Optional_Data<OBJECT_TYPE>::setObject(Object&& object)
{
    d_object = std::move(object);
}

template <typename    OBJECT_TYPE>
template <typename... OBJECT_CONSTRUCTOR_ARGUMENTS>
void Optional_Data<OBJECT_TYPE>::createInPlace(
                                        OBJECT_CONSTRUCTOR_ARGUMENTS&&... args)
{
    new (&d_object)
                   Object(std::forward<OBJECT_CONSTRUCTOR_ARGUMENTS>(args)...);
}

template <typename OBJECT_TYPE>
void Optional_Data<OBJECT_TYPE>::destroyObject()
{
    d_object.~Object();
}

// ACCESSORS
template <typename OBJECT_TYPE>
const OBJECT_TYPE& Optional_Data<OBJECT_TYPE>::object() const
{
    return d_object;
}

                             // ------------------
                             // class OptionalUtil
                             // ------------------

// CLASS METHODS
template <typename LHS_OBJECT_TYPE, typename RHS_OBJECT_TYPE>
inline
void OptionalUtil::copy(Optional_Data<LHS_OBJECT_TYPE>        *output,
                        bool                                  *outputIsNull,
                        const Optional_Data<RHS_OBJECT_TYPE>&  data,
                        bool                                   dataIsNull)
{
    if (!*outputIsNull) {
        output->destroyObject();
    }
    *outputIsNull = dataIsNull;
    Optional_DataUtil::copy(output, data, dataIsNull);
}

template <typename LHS_OBJECT_TYPE, typename RHS_OBJECT_TYPE>
inline
void OptionalUtil::move(Optional_Data<LHS_OBJECT_TYPE>   *output,
                        bool                             *outputIsNull,
                        Optional_Data<RHS_OBJECT_TYPE>&&  data,
                        bool                              dataIsNull)
{
    if (!*outputIsNull) {
        output->destroyObject();
    }
    *outputIsNull = dataIsNull;
    Optional_DataUtil::move(output, std::move(data), dataIsNull);
}

                         // ---------------------------
                         // class Optional<OBJECT_TYPE>
                         // ---------------------------

// LOCAL FUNCTIONS
template <typename LHS_OBJECT_TYPE, typename RHS_OBJECT_TYPE>
inline
void Optional_DataUtil::copy(Optional_Data<LHS_OBJECT_TYPE>        *output,
                             const Optional_Data<RHS_OBJECT_TYPE>&  data,
                             bool                                   dataIsNull)
{
    if (!dataIsNull) {
        output->createInPlace(data.object());
    }
}

template <typename LHS_OBJECT_TYPE, typename RHS_OBJECT_TYPE>
inline
void Optional_DataUtil::move(Optional_Data<LHS_OBJECT_TYPE>   *output,
                             Optional_Data<RHS_OBJECT_TYPE>&&  data,
                             bool                              dataIsNull)
{
    if (!dataIsNull) {
        output->createInPlace(std::move(data.object()));
    }
}


// CREATORS
template <typename OBJECT_TYPE>
inline
Optional<OBJECT_TYPE>::Optional()
    : d_isNull(true)
    , d_data()
{
}

template <typename OBJECT_TYPE>
inline
Optional<OBJECT_TYPE>::Optional(const Optional& original)
    : d_isNull(original.d_isNull)
    , d_data()
{
    Optional_DataUtil::copy(&d_data, original.d_data, original.d_isNull);
}

template <typename OBJECT_TYPE>
inline
Optional<OBJECT_TYPE>::Optional(Optional&& original)
    : d_isNull(original.d_isNull)
    , d_data()
{
    Optional_DataUtil::move(&d_data,
                            std::move(original.d_data),
                            original.d_isNull);
}

template <typename       OBJECT_TYPE>
template <typename OTHER_OBJECT_TYPE>
inline
Optional<OBJECT_TYPE>::Optional(const Optional<OTHER_OBJECT_TYPE>& original)
    : d_isNull(original.d_isNull)
    , d_data()
{
    Optional_DataUtil::copy(&d_data, original.d_data, original.d_isNull);
}

template <typename       OBJECT_TYPE>
template <typename OTHER_OBJECT_TYPE>
inline
Optional<OBJECT_TYPE>::Optional(Optional<OTHER_OBJECT_TYPE>&& original)
    : d_isNull(original.d_isNull)
    , d_data()
{
    Optional_DataUtil::move(&d_data,
                            std::move(original.d_data),
                            original.d_isNull);
}

template <typename OBJECT_TYPE>
inline
Optional<OBJECT_TYPE>::Optional(const Object& object)
    : d_isNull(false)
    , d_data(object)
{
}

template <typename OBJECT_TYPE>
inline
Optional<OBJECT_TYPE>::Optional(Object&& object)
    : d_isNull(false)
    , d_data(std::move(object))
{
}

template <typename    OBJECT_TYPE>
template <typename... OBJECT_CONSTRUCTOR_ARGUMENTS>
inline
Optional<OBJECT_TYPE>::Optional(OBJECT_CONSTRUCTOR_ARGUMENTS&&... arguments)
    : d_isNull(false)
    , d_data(std::forward<OBJECT_CONSTRUCTOR_ARGUMENTS>(arguments)...)
{
}

template <typename OBJECT_TYPE>
inline
Optional<OBJECT_TYPE>::~Optional()
{
    if (!d_isNull) {
        d_data.destroyObject();
    }
}

// MANIPULATORS
template <typename OBJECT_TYPE>
Optional<OBJECT_TYPE>& Optional<OBJECT_TYPE>::operator=(
                                                       const Optional& original)
{
    OptionalUtil::copy(&d_data, &d_isNull, original.d_data, original.d_isNull);
    return *this;
}

template <typename OBJECT_TYPE>
Optional<OBJECT_TYPE>& Optional<OBJECT_TYPE>::operator=(Optional&& original)
{
    OptionalUtil::move(&d_data,
                       &d_isNull,
                       std::move(original.d_data),
                       original.d_isNull);
    return *this;
}

template <typename       OBJECT_TYPE>
template <typename OTHER_OBJECT_TYPE>
Optional<OBJECT_TYPE>& Optional<OBJECT_TYPE>::operator=(
                                   const Optional<OTHER_OBJECT_TYPE>& original)
{
    OptionalUtil::copy(&d_data, &d_isNull, original.d_data, original.d_isNull);
    return *this;
}

template <typename       OBJECT_TYPE>
template <typename OTHER_OBJECT_TYPE>
Optional<OBJECT_TYPE>& Optional<OBJECT_TYPE>::operator=(
                                        Optional<OTHER_OBJECT_TYPE>&& original)
{
    OptionalUtil::move(&d_data,
                       &d_isNull,
                       std::move(original.d_data),
                       original.d_isNull);
    return *this;
}

template <typename OBJECT_TYPE>
Optional<OBJECT_TYPE>& Optional<OBJECT_TYPE>::operator=(const Object& object)
{
    if (!d_isNull) {
        d_data.destroyObject();
    }
    d_data.setObject(object);
    return *this;
}

template <typename OBJECT_TYPE>
Optional<OBJECT_TYPE>& Optional<OBJECT_TYPE>::operator=(Object&& object)
{
    if (!d_isNull) {
        d_data.destroyObject();
    }
    d_data.setObject(std::move(object));
    return *this;
}

template <typename       OBJECT_TYPE>
template <typename OTHER_OBJECT_TYPE>
Optional<OBJECT_TYPE>& Optional<OBJECT_TYPE>::operator=(
                                                    OTHER_OBJECT_TYPE&& object)
{
    if (!d_isNull) {
        d_data.destroyObject();
    }
    d_data.setObject(std::move(object));
    return *this;
}

template <typename OBJECT_TYPE>
OBJECT_TYPE& Optional<OBJECT_TYPE>::operator*()
{
    return d_data.object();
}

template <typename OBJECT_TYPE>
OBJECT_TYPE *Optional<OBJECT_TYPE>::operator->()
{
    return &d_data.object();
}

template <typename OBJECT_TYPE>
OBJECT_TYPE& Optional<OBJECT_TYPE>::value()
{
    return d_data.object();
}

template <typename    OBJECT_TYPE>
template <typename... OBJECT_CONSTRUCTOR_ARGUMENTS>
void Optional<OBJECT_TYPE>::createInPlace(
                                   OBJECT_CONSTRUCTOR_ARGUMENTS&&... arguments)
{
    if (!d_isNull) {
        d_data.destroyObject();
    }
    d_data.createInPlace(
                     std::forward<OBJECT_CONSTRUCTOR_ARGUMENTS>(arguments)...);
}

template <typename OBJECT_TYPE>
void Optional<OBJECT_TYPE>::reset()
{
    if (!d_isNull) {
        d_data.destroyObject();
    }
}

// ACCESSORS
template <typename OBJECT_TYPE>
const OBJECT_TYPE& Optional<OBJECT_TYPE>::operator*() const
{
    return d_data.object();
}

template <typename OBJECT_TYPE>
const OBJECT_TYPE *Optional<OBJECT_TYPE>::operator->() const
{
    return &d_data.object();
}

template <typename OBJECT_TYPE>
const OBJECT_TYPE& Optional<OBJECT_TYPE>::value() const
{
    return d_data.object();
}

template <typename OBJECT_TYPE>
bool Optional<OBJECT_TYPE>::isNull() const
{
    return d_isNull;
}

template <typename OBJECT_TYPE>
Optional<OBJECT_TYPE>::operator bool() const
{
    return !d_isNull;
}

// FREE OPERATORS
template <typename LHS_OBJECT_TYPE, typename RHS_OBJECT_TYPE>
bool operator==(const Optional<LHS_OBJECT_TYPE>& lhs,
                const Optional<RHS_OBJECT_TYPE>& rhs)
{
    if (lhs.isNull()) {
        if (rhs.isNull()) {
            return true;                                              // RETURN
        }
        return false;                                                 // RETURN
    }
    if (rhs.isNull()) {
        return false;                                                 // RETURN
    }
    return lhs.value() == rhs.value();
}

template <typename LHS_OBJECT_TYPE, typename RHS_OBJECT_TYPE>
bool operator!=(const Optional<LHS_OBJECT_TYPE>& lhs,
                const Optional<RHS_OBJECT_TYPE>& rhs)
{
    if (lhs.isNull()) {
        if (rhs.isNull()) {
            return false;                                             // RETURN
        }
        return true;                                                  // RETURN
    }
    if (rhs.isNull()) {
        return true;                                                  // RETURN
    }
    return lhs.value() != rhs.value();
}


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
//Directory DirectoryUtil::open(const std::string& name)
//{
//    return Directory(posix::opendir(name.c_str()));
//}
//
//Cursor<DirectoryEntry> DirectoryUtil::list(const std::string& name)
//{
//    std::unique_ptr<DirectoryEntryCursor> cursor =
//                            std::make_unique<DirectoryEntryCursor>(open(name));
//    return Cursor<DirectoryEntry>(std::move(cursor));
//}

} // close unnamed namespace

// ============================================================================
//                                 UNIT TESTS
// ============================================================================

namespace {

} // close unnamed namespace
