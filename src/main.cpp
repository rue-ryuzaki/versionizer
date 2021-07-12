#include <argparse/argparse.hpp>

#include "versionizer.hpp"

int main(int argc, char* argv[])
{
    auto parser = argparse::ArgumentParser(argc, argv)
            .fromfile_prefix_chars("@")
            .description("Version manager for C/C++ projects");
    parser.add_argument("--type")
            .choices({ "M", "MM", "MR", "MMP", "MMR", "MMPR" })
            .required(true).help("version type");
    parser.add_argument("--source")
            .required(true).help("source file with version");
    parser.add_argument("--program")
            .required(true).help("program name in source file");
    parser.add_argument("--apply")
            .choices({ "major", "minor", "patch", "rc", "rc-major", "rc-minor" })
            .default_value("")
            .help("version patch type");

    auto args = parser.parse_args();

    versionizer::Versionizer ver;
    ver.setType(args.get<std::string>("type"));

    auto versionFile = args.get<std::string>("source");
    auto programName = args.get<std::string>("program");

    auto version = versionizer::loadVersionFromFile(versionFile, programName);
    std::cout << "version v" << version.to_string(ver.type()) << std::endl;

    auto versionPatch = args.get<std::string>("apply");
    if (!versionPatch.empty()) {
        if (versionPatch == "major") {
            version.apply_major(ver.type());
        } else if (versionPatch == "minor") {
            version.apply_minor(ver.type());
        } else if (versionPatch == "patch") {
            version.apply_patch(ver.type());
        } else if (versionPatch == "rc") {
            version.apply_rc(ver.type());
        } else if (versionPatch == "rc-major") {
            version.apply_rc_major(ver.type());
        } else if (versionPatch == "rc-minor") {
            version.apply_rc_minor(ver.type());
        } else {
            throw std::logic_error("invalid apply patch type '" + versionPatch + "'");
        }
        std::cout << "version v" << version.to_string(ver.type()) << std::endl;
    }
    return 0;
}
