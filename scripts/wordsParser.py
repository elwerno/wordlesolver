input_file_path = "submodules/words_alpha.txt"
output_file_path = "database/5_letter_words.txt"


def words_parser():
    try:
        with open(input_file_path, "r") as input:
            with open(output_file_path, "w") as output:
                # Filter out all 5 letter words
                for line in input:
                    word = line.strip()
                    if len(word) == 5:
                        output.write(word + "\n")
    except FileNotFoundError:
        print(f"The file {input_file_path} does not exist.")
    except IOError as e:
        print(f"An error occurred while trying to read the file: {e}")


if __name__ == "__main__":
    words_parser()
