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

class Namespace:
	def __init__(self, name):
		self.name = name
		self.elememts = []

	def add(self, new_element):
		self.elememts.append(new_element)

	def to_string(self):
		string_result = f"namespace {self.name}\n"
		string_result += "{\n\n"
		for e in self.elememts:
			string_result += e.to_string()
			string_result += "\n"
		string_result += "}\n"
		return string_result

class CompileTimeConstant:
	def __init__(self, name, its_type, value):
		self.name = name
		self.its_type = its_type
		self.value = value

	def to_string(self):
		return f"constexpr {self.its_type} {self.name} = {self.value};"

class InitMapFunction:
	def __init__(self, name, return_type):
		self.name = name
		self.return_type = return_type
		self.keys = []
		self.values = []

	def add_key(self, new_key):
		self.keys.append(new_key)

	def add_value(self, new_value):
		self.values.append(new_value)

	def to_string(self):
		result_string = f"constexpr {self.return_type} {self.name}()\n"
		result_string += "{\n"
		result_string += f"\t{self.return_type} map\n"
		result_string += "\t{\n"

		# add keys
		result_string += "\t\t// Keys\n"
		result_string += "\t\t{\n"
		is_first_elem = True
		for k in self.keys:
			if not is_first_elem:
				result_string += ",\n"
			is_first_elem = False
			result_string += f"\t\t\t\"{k}\""
		result_string += "\n\t\t},\n"

		# add values
		result_string += "\t\t// Values\n"
		result_string += "\t\t{\n"
		is_first_elem = True
		for v in self.values:
			if not is_first_elem:
				result_string += ",\n"
			is_first_elem = False
			result_string += f"\t\t\t{v}"
		result_string += "\n\t\t}\n"
		
		result_string += "\t};\n"
		result_string += "\treturn map;\n"
		result_string += "}\n"
		return result_string

def read_json_file(filename: str):
	with open(filename, "r") as file:
		return json.load(file)

def read_lines_file(filename: str):
	with open(filename, "r") as file:
		return file.readlines(106000)

def write_to_file(filename: str, content: str):
	with open(filename, "w") as file:
		return file.write(content)		

def generate_word_to_word(output_file: str, json_content):
	log(INFO, "Word to word", "Generation starting")

	generated_code = "#pragma once\n\n"
	generated_code += "#include <string_view>\n\n"
	generated_code += "#include <TranslatorCallable.hpp>\n"
	generated_code += "#include <StaticMap.hpp>\n"
	generated_code += "#include <WordTranslations.hpp>\n\n"

	size = CompileTimeConstant("WORD_TRANSLATOR_SIZE", "std::size_t", len(json_content["words"]))

	fun = InitMapFunction("load_word_translator_map", "StaticMap<std::string_view, TranslatorCallable, WORD_TRANSLATOR_SIZE>")
	for word in json_content["words"]:
		fun.add_key(word["word"])

		value_line = "createWordTranslationContainer("
		is_first_equivalent = True
		for equivalents in word["equivalents"]:
			if not is_first_equivalent:
				value_line += ", "	
			is_first_equivalent = False
			value_line += "WordTranslation{ " + str(equivalents["weight"]) + ", \"" + equivalents["chars"] + "\" }"
		value_line += ")"
		fun.add_value(value_line)

	generated_namespace = Namespace("generated")
	generated_namespace.add(size)
	generated_namespace.add(fun)

	yolol_namespace = Namespace("YololTranslator")
	yolol_namespace.add(generated_namespace)
	generated_code += yolol_namespace.to_string()

	write_to_file(output_file, generated_code)
	log(INFO, "Word to word", "Generation done")

def generate_word_to_phonem(output_file: str, lines_file):
	log(INFO, "Word to phonem", "Generation starting")
	write_to_file(output_file, "yolol")
	log(INFO, "Word to phonem", "Generation done")

def generate_phonem_to_chars(output_file: str, json_content):
	log(INFO, "Phonem to chars", "Generation starting")
	write_to_file(output_file, "yolol")
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

	generate_word_to_word(args.output_dir + "/WordTranslatorGenerated.hpp", read_json_file(args.word_to_word_file))
	generate_word_to_phonem(args.output_dir + "/WordToPhonemGenerated.hpp", read_lines_file(args.word_to_phonem_file))
	generate_phonem_to_chars(args.output_dir + "/PhonemToStringGenerated.hpp", read_json_file(args.phonem_to_char_file))

	log(INFO, "Main", "Program is over.")

if __name__ == "__main__":
	main()