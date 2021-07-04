#include <argparse/argparse.hpp>

#include "versionizer.hpp"

int main(int argc, char* argv[])
{
    auto parser = argparse::ArgumentParser(argc, argv)
            .description("Version manager for C/C++ projects");
    parser.add_argument("--type").choices({ "M", "MM", "MR", "MMP", "MMR", "MMPR" })
            .required(true)
            .help("Version type");

    auto args = parser.parse_args();

    versionizer::Versionizer ver;
    ver.setType(args.get<std::string>("type"));

    return 0;
}
