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
    parser.add_argument("--patch")
            .action("store_true").help("patch version in source file");

    auto args = parser.parse_args();

    versionizer::Versionizer ver;
    ver.setType(args.get<std::string>("type"));

    auto versionFile = args.get<std::string>("source");
    auto programName = args.get<std::string>("program");
    std::cout << "program " << programName << std::endl;
    std::cout << "analize " << versionFile << std::endl;

    auto version = versionizer::Version::loadFromFile(versionFile, programName);
    std::cout << "old version v" << version.to_string(ver.type()) << std::endl;

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
            throw std::logic_error("invalid apply version patch type '" + versionPatch + "'");
        }
        std::cout << "new version v" << version.to_string(ver.type()) << std::endl;
        if (args.get<bool>("patch")) {
            version.patchFile(versionFile, programName);
        }
    }
    return 0;
}
