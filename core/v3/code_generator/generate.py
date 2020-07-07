import argparse
import json
from termcolor import colored, cprint

INFO = "Info"
WARNING = "Warning"
ERROR = "Error"

def log(log_type, step, message):
	if log_type == INFO:
		colored_log_type = colored(log_type, 'green', attrs=['bold'])
	elif log_type == WARNING:
		colored_log_type = colored(log_type, 'yellow', attrs=['bold'])
	elif log_type == ERROR:
		colored_log_type = colored(log_type, 'red', attrs=['bold'])
	else:
		colored_log_type = colored(log_type, 'blue', attrs=['bold'])
	
	colored_step = colored(step, 'blue')
	print(colored_log_type + ': ' + colored_step + ' => ' + message)


def read_json_file(filename: str):
	with open(filename, "r") as file:
		return json.load(file)

def read_lines_file(filename: str):
	with open(filename, "r") as file:
		return file.readlines(106000)

def generate_word_to_word(json_content):
	log(INFO, "Word to word", "Generation starting")
	log(INFO, "Word to word", "Generation done")

def generate_word_to_phonem(lines_file):
	log(INFO, "Word to phonem", "Generation starting")
	log(INFO, "Word to phonem", "Generation done")

def generate_phonem_to_chars(json_content):
	log(INFO, "Phonem to chars", "Generation starting")
	log(INFO, "Phonem to chars", "Generation done")

def main():
	log(INFO, "Main", "Program is starting.")

	parser = argparse.ArgumentParser(description='Generate dictionnaries for YololTranslator Core V3')
	parser.add_argument('-wwf', '--word-to-word-file', default="./assets/word_to_word_dict_fr.json", help='Path to the input file for word to word translation.')
	parser.add_argument('-wpf', '--word-to-phonem-file', default="./assets/fr.dict", help='Path to the input file for word to phonem translation.')
	parser.add_argument('-pcf', '--phonem-to-char-file', default="./assets/french_dico.json", help='Path to the input file for phonem to characters translation.')
	parser.add_argument('-o', '--output-dir', default="./lib/generated", help='Path to the output directory.')
	args = parser.parse_args()

	log(INFO, "Main", "Arguments parsing done.")

	generate_phonem_to_chars(read_json_file(args.word_to_word_file))
	generate_word_to_phonem(read_lines_file(args.word_to_phonem_file))
	generate_word_to_word(read_json_file(args.phonem_to_char_file))

	log(INFO, "Main", "Program is over.")

if __name__ == "__main__":
	main()