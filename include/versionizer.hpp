/*
 * MIT License
 *
 * Version organizer for C/C++ (Versionizer v0.0.0)
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

#include <fstream>
#include <regex>
#include <stdexcept>
#include <string>

#define VERSIONIZER_VERSION_MAJOR 0
#define VERSIONIZER_VERSION_MINOR 0
#define VERSIONIZER_VERSION_PATCH 0
#define VERSIONIZER_VERSION_RC 0

namespace versionizer {
enum Type {
    None,

    M,
    MM,
    MR,
    MMP,
    MMR,
    MMPR
};

struct Version
{
    int major;
    int minor;
    int patch;
    int rc;

    Version& apply_major(Type type)
    {
        validate(type);
        switch (type) {
            case M :
                ++major;
                break;
            case MM :
                ++major;
                minor = 0;
                break;
            case MR :
                if (rc == 0) {
                    ++major;
                } else {
                    rc = 0;
                }
                break;
            case MMP :
                ++major;
                minor = 0;
                patch = 0;
                break;
            case MMR :
                if (rc == 0) {
                    ++major;
                    minor = 0;
                } else {
                    if (minor > 0) {
                        throw std::invalid_argument("error: invalid minor version");
                    }
                    rc = 0;
                }
                break;
            case MMPR :
                if (rc == 0) {
                    ++major;
                    minor = 0;
                    patch = 0;
                } else {
                    if (minor > 0) {
                        throw std::invalid_argument("error: invalid minor version");
                    }
                    if (patch > 0) {
                        throw std::invalid_argument("error: invalid patch version");
                    }
                    rc = 0;
                }
                break;
            default :
                throw std::logic_error("error: invalid version type");
        }
        return *this;
    }

    Version& apply_minor(Type type)
    {
        validate(type);
        switch (type) {
            case MM :
                ++minor;
                break;
            case MMP :
                ++minor;
                patch = 0;
                break;
            case MMR :
                if (rc == 0) {
                    ++minor;
                } else {
                    rc = 0;
                }
                break;
            case MMPR :
                if (rc == 0) {
                    ++minor;
                    patch = 0;
                } else {
                    if (patch > 0) {
                        throw std::invalid_argument("error: invalid patch version");
                    }
                    rc = 0;
                }
                break;
            default :
                throw std::logic_error("error: invalid version type");
        }
        return *this;
    }

    Version& apply_patch(Type type)
    {
        validate(type);
        switch (type) {
            case MMP :
                ++patch;
                break;
            case MMPR :
                if (rc == 0) {
                    ++patch;
                } else {
                    throw std::invalid_argument("error: invalid rc version");
                }
                break;
            default :
                throw std::logic_error("error: invalid version type");
        }
        return *this;
    }

    Version& apply_rc(Type type)
    {
        validate(type);
        switch (type) {
            case MR :
                if (rc == 0) {
                    ++major;
                } else if (major <= 0) {
                    throw std::invalid_argument("error: invalid major version");
                }
                ++rc;
                break;
            case MMR :
                if (rc == 0) {
                    ++major;
                    minor = 0;
                } else if (major <= 0) {
                    throw std::invalid_argument("error: invalid minor version");
                } else if (minor > 0) {
                    throw std::invalid_argument("error: invalid minor version");
                }
                ++rc;
                break;
            case MMPR :
                if (rc == 0) {
                    ++minor;
                } else if (minor <= 0) {
                    throw std::invalid_argument("error: invalid minor version");
                } else if (patch > 0) {
                    throw std::invalid_argument("error: invalid patch version");
                }
                ++rc;
                break;
            default :
                throw std::logic_error("error: invalid version type");
        }
        return *this;
    }

    Version& apply_rc_major(Type type)
    {
        validate(type);
        switch (type) {
            case MR :
                if (rc == 0) {
                    ++major;
                } else if (major <= 0) {
                    throw std::invalid_argument("error: invalid major version");
                }
                ++rc;
                break;
            case MMR :
                if (rc == 0) {
                    ++major;
                    minor = 0;
                } else if (major <= 0) {
                    throw std::invalid_argument("error: invalid major version");
                } else if (minor > 0) {
                    throw std::invalid_argument("error: invalid minor version");
                }
                ++rc;
                break;
            case MMPR :
                if (rc == 0) {
                    ++major;
                    minor = 0;
                    patch = 0;
                } else if (major <= 0) {
                    throw std::invalid_argument("error: invalid major version");
                } else if (minor > 0) {
                    throw std::invalid_argument("error: invalid minor version");
                } else if (patch > 0) {
                    throw std::invalid_argument("error: invalid patch version");
                }
                ++rc;
                break;
            default :
                throw std::logic_error("error: invalid version type");
        }
        return *this;
    }

    Version& apply_rc_minor(Type type)
    {
        validate(type);
        switch (type) {
            case MMPR :
                if (rc == 0) {
                    ++minor;
                    patch = 0;
                } else if (minor <= 0) {
                    throw std::invalid_argument("error: invalid minor version");
                } else if (patch > 0) {
                    throw std::invalid_argument("error: invalid patch version");
                }
                ++rc;
                break;
            default :
                throw std::logic_error("error: invalid version type");
        }
        return *this;
    }

    std::string to_string(Type type) const
    {
        validate(type);
        switch (type) {
            case M :
                return std::to_string(major);
            case MM :
                return std::to_string(major)
                        + "." + std::to_string(minor);
            case MR :
                if (rc == 0) {
                    return std::to_string(major);
                } else {
                    return std::to_string(major)
                            + "-rc" + std::to_string(rc);
                }
            case MMP :
                return std::to_string(major)
                        + "." + std::to_string(minor)
                        + "." + std::to_string(patch);
            case MMR :
                if (rc == 0) {
                    return std::to_string(major)
                            + "." + std::to_string(minor);
                } else {
                    return std::to_string(major)
                            + "-rc" + std::to_string(rc);
                }
            case MMPR :
                if (rc == 0) {
                    return std::to_string(major)
                            + "." + std::to_string(minor)
                            + "." + std::to_string(patch);
                } else {
                    return std::to_string(major)
                            + "." + std::to_string(minor)
                            + "-rc" + std::to_string(rc);
                }
            default :
                throw std::logic_error("error: invalid version type");
        }
    }

private:
    void validate(Type type) const
    {
        switch (type) {
            case M :
                if (major < 0) {
                    throw std::invalid_argument("error: invalid major version");
                }
                break;
            case MM :
                if (major < 0) {
                    throw std::invalid_argument("error: invalid major version");
                }
                if (minor < 0) {
                    throw std::invalid_argument("error: invalid minor version");
                }
                break;
            case MR :
                if (major < 0) {
                    throw std::invalid_argument("error: invalid major version");
                }
                if (rc < 0) {
                    throw std::invalid_argument("error: invalid rc version");
                }
                break;
            case MMP :
                if (major < 0) {
                    throw std::invalid_argument("error: invalid major version");
                }
                if (minor < 0) {
                    throw std::invalid_argument("error: invalid minor version");
                }
                if (patch < 0) {
                    throw std::invalid_argument("error: invalid patch version");
                }
                break;
            case MMR :
                if (major < 0) {
                    throw std::invalid_argument("error: invalid major version");
                }
                if (minor < 0) {
                    throw std::invalid_argument("error: invalid minor version");
                }
                if (rc < 0) {
                    throw std::invalid_argument("error: invalid rc version");
                }
                break;
            case MMPR :
                if (major < 0) {
                    throw std::invalid_argument("error: invalid major version");
                }
                if (minor < 0) {
                    throw std::invalid_argument("error: invalid minor version");
                }
                if (patch < 0) {
                    throw std::invalid_argument("error: invalid patch version");
                }
                if (rc < 0) {
                    throw std::invalid_argument("error: invalid rc version");
                }
                break;
            default :
                throw std::logic_error("error: invalid version type");
        }
    }
};

static Version loadVersionFromFile(std::string const& file, std::string const& name)
{
    Version res{ -1, -1, -1, -1 };
    std::ifstream is(file.c_str());
    if (is.is_open()) {
        std::regex const major("#define[\\s-[\\r\\n]]*" + name + "_VERSION_MAJOR[\\s-[\\r\\n]]*([0-9]*)");
        std::regex const minor("#define[\\s-[\\r\\n]]*" + name + "_VERSION_MINOR[\\s-[\\r\\n]]*([0-9]*)");
        std::regex const patch("#define[\\s-[\\r\\n]]*" + name + "_VERSION_PATCH[\\s-[\\r\\n]]*([0-9]*)");
        std::regex const rc("#define[\\s-[\\r\\n]]*" + name + "_VERSION_RC[\\s-[\\r\\n]]*([0-9]*)");
        std::smatch match;
        std::string line;
        while (std::getline(is, line)) {
            if (std::regex_search(line, match, major)) {
                res.major = std::stoi(std::string(match[1]));
            } else if (std::regex_search(line, match, minor)) {
                res.minor = std::stoi(std::string(match[1]));
            } else if (std::regex_search(line, match, patch)) {
                res.patch = std::stoi(std::string(match[1]));
            } else if (std::regex_search(line, match, rc)) {
                res.rc = std::stoi(std::string(match[1]));
            }
        }
        is.close();
    }
    return res;
}

class Versionizer
{
public:
    Versionizer()
        : m_type(None)
    { }

    void setType(std::string const& value)
    {
        if (value == "M") {
            m_type = M;
        } else if (value == "MM") {
            m_type = MM;
        } else if (value == "MR") {
            m_type = MR;
        } else if (value == "MMP") {
            m_type = MMP;
        } else if (value == "MMR") {
            m_type = MMR;
        } else if (value == "MMPR") {
            m_type = MMPR;
        } else {
            throw std::invalid_argument("error: unknown version type '" + value + "'");
        }
    }

    Type type() const
    {
        return m_type;
    }

    std::string versionToString(Version const& ver) const
    {
        return ver.to_string(type());
    }

private:
    Type m_type;
};
} // versionizer

#endif // _VERSIONIZER_VERSIONIZER_HPP_
