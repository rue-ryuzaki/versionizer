/*
 * MIT License
 *
 * Version organizer for C/C++ (Versionizer v0.1-rc2)
 *
 * Copyright (c) 2021 Golubchikov Mihail
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _VERSIONIZER_VERSIONIZER_HPP_
#define _VERSIONIZER_VERSIONIZER_HPP_

#include <string>

#define VERSIONIZER_VERSION_MAJOR 0
#define VERSIONIZER_VERSION_MINOR 1
#define VERSIONIZER_VERSION_PATCH 0
#define VERSIONIZER_VERSION_RC 2

namespace versionizer {
// -----------------------------------------------------------------------------
enum Type {
    None,

    M,
    MM,
    MR,
    MMP,
    MMR,
    MMPR
};

// -----------------------------------------------------------------------------
// -- Version ------------------------------------------------------------------
// -----------------------------------------------------------------------------
struct Version
{
    int major;
    int minor;
    int patch;
    int rc;

    Version& apply_major(Type type);
    Version& apply_minor(Type type);
    Version& apply_patch(Type type);
    Version& apply_rc(Type type);
    Version& apply_rc_major(Type type);
    Version& apply_rc_minor(Type type);

    std::string to_string(Type type) const;

    static Version from_string(std::string const& str);
    static Version loadFromFile(std::string const& file, std::string const& name);

    void patchFile(std::string const& file, std::string const& name) const;

private:
    void validate(Type type) const;
};

// -----------------------------------------------------------------------------
// -- Versionizer --------------------------------------------------------------
// -----------------------------------------------------------------------------
class Versionizer
{
public:
    Versionizer();

    void setType(std::string const& value);

    Type type() const;

    std::string versionToString(Version const& ver) const;

    void patchFile(std::string const& file, Version const& oldVersion, Version const& newVersion, bool replaceOnce = true) const;

private:
    Type m_type;
};
} // versionizer

#endif // _VERSIONIZER_VERSIONIZER_HPP_
