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

#include <stdexcept>
#include <string>

#define VERSIONIZER_VERSION_MAJOR 0
#define VERSIONIZER_VERSION_MINOR 0
#define VERSIONIZER_VERSION_PATCH 0
#define VERSIONIZER_VERSION_RC 0

namespace versionizer {
struct Version
{
    int major;
    int minor;
    int patch;
    int rc;
};

class Versionizer
{
public:
    enum Type {
        None,

        M,
        MM,
        MR,
        MMP,
        MMR,
        MMPR
    };

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
        validateVersion(ver);
        switch (m_type) {
            case M :
                return std::to_string(ver.major);
            case MM :
                return std::to_string(ver.major)
                        + "." + std::to_string(ver.minor);
            case MR :
                if (ver.rc == 0) {
                    return std::to_string(ver.major);
                } else {
                    return std::to_string(ver.major)
                            + "-rc" + std::to_string(ver.rc);
                }
            case MMP :
                return std::to_string(ver.major)
                        + "." + std::to_string(ver.minor)
                        + "." + std::to_string(ver.patch);
            case MMR :
                if (ver.rc == 0) {
                    return std::to_string(ver.major)
                            + "." + std::to_string(ver.minor);
                } else {
                    return std::to_string(ver.major)
                            + "-rc" + std::to_string(ver.rc);
                };
            case MMPR :
                if (ver.rc == 0) {
                    return std::to_string(ver.major)
                            + "." + std::to_string(ver.minor)
                            + "." + std::to_string(ver.patch);
                } else {
                    return std::to_string(ver.major)
                            + "." + std::to_string(ver.minor)
                            + "-rc" + std::to_string(ver.rc);
                }
            default :
                throw std::logic_error("error: invalid version type");
        }
    }

private:
    void validateVersion(Version const& ver) const
    {
        switch (m_type) {
            case M :
                if (ver.major < 0) {
                    throw std::invalid_argument("error: invalid major version");
                }
                break;
            case MM :
                if (ver.major < 0) {
                    throw std::invalid_argument("error: invalid major version");
                }
                if (ver.minor < 0) {
                    throw std::invalid_argument("error: invalid minor version");
                }
                break;
            case MR :
                if (ver.major < 0) {
                    throw std::invalid_argument("error: invalid major version");
                }
                if (ver.rc < 0) {
                    throw std::invalid_argument("error: invalid rc version");
                }
                break;
            case MMP :
                if (ver.major < 0) {
                    throw std::invalid_argument("error: invalid major version");
                }
                if (ver.minor < 0) {
                    throw std::invalid_argument("error: invalid minor version");
                }
                if (ver.patch < 0) {
                    throw std::invalid_argument("error: invalid patch version");
                }
                break;
            case MMR :
                if (ver.major < 0) {
                    throw std::invalid_argument("error: invalid major version");
                }
                if (ver.minor < 0) {
                    throw std::invalid_argument("error: invalid minor version");
                }
                if (ver.rc < 0) {
                    throw std::invalid_argument("error: invalid rc version");
                }
                break;
            case MMPR :
                if (ver.major < 0) {
                    throw std::invalid_argument("error: invalid major version");
                }
                if (ver.minor < 0) {
                    throw std::invalid_argument("error: invalid minor version");
                }
                if (ver.patch < 0) {
                    throw std::invalid_argument("error: invalid patch version");
                }
                if (ver.rc < 0) {
                    throw std::invalid_argument("error: invalid rc version");
                }
                break;
            default :
                throw std::logic_error("error: invalid version type");
        }
    }

    Type m_type;
};
} // versionizer

#endif // _VERSIONIZER_VERSIONIZER_HPP_
