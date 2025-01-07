env_file = "config.env"
header_file = "main/config.h"

def generate_config():
    with open(env_file, "r") as env, open(header_file, "w") as header:
        header.write("#ifndef CONFIG_H\n")
        header.write("#define CONFIG_H\n\n")
        for line in env:
            line = line.strip()
            if not line or line.startswith("#"):
                continue
            key, value = line.split("=", 1)
            value = value.strip().strip('"')
            header.write(f'#define {key} "{value}"\n')
        header.write("\n#endif // CONFIG_H\n")

if __name__ == "__main__":
    generate_config()
    print(f"Generated {header_file} from {env_file}")
