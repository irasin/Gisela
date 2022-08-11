import os
import argparse
import glob

CWD = os.path.dirname(os.path.abspath(__file__))
TARGET_CPP_NAME = os.path.join(CWD, "cl_src.cc")


def string_to_hex_char_list(string):
    hex_char = [hex(ord(char)) for char in string]
    return hex_char


def main():
    parser = argparse.ArgumentParser("convert cl code to c++ src")

    parser.add_argument("--cl_dir",
                        type=str,
                        default=None,
                        help="dir path of cl code")
    parser.add_argument("--target_cpp_name",
                        type=str,
                        default=None,
                        help="generated c++ file name")
    args = parser.parse_args()

    if args.cl_dir is None:
        args.cl_dir = CWD

    cl_src = glob.glob(f"{args.cl_dir}/*.cl")
    if not cl_src:
        raise ValueError("cl src file not exists")

    opencl_src_map = dict()
    for cl_file in cl_src:
        with open(cl_file, "r") as f:
            data = f.read()

        program_name = os.path.splitext(os.path.basename(cl_file))[0]
        opencl_src_map[program_name] = string_to_hex_char_list(data)

    if args.target_cpp_name is None:
        args.target_cpp_name = TARGET_CPP_NAME

    opencl_src_code = "#include <map>\n"
    opencl_src_code += "#include <vector>\n"
    opencl_src_code += "#include <string>\n"
    opencl_src_code += "namespace gisela {\n\n"
    opencl_src_code += "extern const std::map<std::string,"
    opencl_src_code += " std::vector<unsigned char>> cl_src = {\n"

    for program, hex_char_list in opencl_src_map.items():
        opencl_src_code += "\t{\""
        opencl_src_code += program
        opencl_src_code += "\", {"
        opencl_src_code += ",".join(hex_char_list)
        opencl_src_code += "}},\n"

    opencl_src_code += "};\n\n"
    opencl_src_code += "}  // namespace gisela\n"

    with open(args.target_cpp_name, "w") as f:
        f.write(opencl_src_code)


if __name__ == "__main__":
    main()
