import argparse
import json
from termcolor import colored, cprint

""" step_colored_text = colored(current_step + ':', 'blue', attrs=['bold'])
text_colored = colored(text, 'green') """

def read_json_file(filename: str):
	with open(filename, "r") as file:
		return json.load(file)

def read_lines_file(filename: str):
	with open(filename, "r") as file:
		return file.readlines(106000)

def generate_word_to_word(json_content):
	pass

def generate_word_to_phonem(lines_file):
	pass

def generate_phonem_to_chars(json_content):
	pass

def main():
	parser = argparse.ArgumentParser(description='Generate dictionnaries for YololTranslator Core V3')
	parser.add_argument('-wwf', '--word-to-word-file', default="./assets/word_to_word_dict_fr.json", help='Path to the input file for word to word translation.')
	parser.add_argument('-wpf', '--word-to-phonem-file', default="./assets/fr.dict", help='Path to the input file for word to phonem translation.')
	parser.add_argument('-pcf', '--phonem-to-char-file', default="./assets/french_dico.json", help='Path to the input file for phonem to characters translation.')
	parser.add_argument('-o', '--output-dir', default="./lib/generated", help='Path to the output directory.')
	args = parser.parse_args()

	generate_phonem_to_chars(read_json_file(args.word_to_word_file))
	generate_word_to_phonem(read_lines_file(args.word_to_phonem_file))
	generate_word_to_word(read_json_file(args.phonem_to_char_file))

if __name__ == "__main__":
	main()