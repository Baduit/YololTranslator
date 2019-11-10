#!/usr/bin/env python3

import argparse
import subprocess
import os
import shutil

class DirExplorer:
	base_dir = os.getcwd()
	core_v1_dir = base_dir + '/core/v1/'
	core_v2_dir = base_dir + '/core/v2/'
	discord_dir = base_dir + '/discord-bot/'
	web_dir = base_dir + '/web/'

	@staticmethod
	def cd_base():
		os.chdir(DirExplorer.base_dir)

	@staticmethod
	def cd_core_v1():
		os.chdir(DirExplorer.core_v1_dir)

	@staticmethod
	def cd_core_v2():
		os.chdir(DirExplorer.core_v2_dir)

	@staticmethod
	def cd_discord():
		os.chdir(DirExplorer.discord_dir)

	@staticmethod
	def cd_web():
		os.chdir(DirExplorer.web_dir)

	@staticmethod
	def cd_build():
		os.chdir('./build/')

	@staticmethod
	def current_dir():
		return os.getcwd()


def call_make():
	log('Compilation')
	subprocess.call(['make'])

def copy_file_in_parent_dir(filename):
	log('Copy file: ' + filename + ' into the right directory.')
	shutil.copy(filename, '..')

def call_deploy():
	log('Launching the module.')
	subprocess.call(['./bash_scripts/deploy.sh'])
	pass

def call_stop():
	log('Kill running Yolol process.')
	subprocess.call(['./bash_scripts/stop.sh'])
	pass

def call_npm_install():
	log('Installation of node.js modules.')
	subprocess.call(['npm', 'install'])
	pass

def call_cmake():
	log('Cmake processing')
	subprocess.call(['cmake', '..'])

parser = argparse.ArgumentParser(description='Graphical user interface for YololTranslator')
parser.add_argument('-k', '--kill', action='store_true', help='Kill existing Yolol processes.')
parser.add_argument('-c', '--cmake', action='store_true', help='Freate build directory and run cmake for the C++ projects, if build dir already exist, it erase it.')
parser.add_argument('-i', '--install', action='store_true', help='Run npm install for the node.js projects.')
parser.add_argument('-p', '--pretty', action='store_true', help='Enable pretty logs (add colors)')
args = parser.parse_args()

if args.pretty:
	from termcolor import colored, cprint

current_step = 'Global step'
def log(text):
	if not args.pretty:
		print(current_step + ':', text)
	else:
		step_colored_text = colored(current_step + ':', 'blue', attrs=['bold'])
		text_colored = colored(text, 'green')
		print(step_colored_text, text_colored)

# If needed kill existing processes
if args.kill:
	current_step = 'Kill running process'
	DirExplorer.cd_discord()
	call_stop()
	DirExplorer.cd_web()
	call_stop()

# Compile core v1 and copy the executable at the right place
current_step = 'Core v1'
log('Setup')
if args.cmake:
	DirExplorer.cd_core_v1()
	os.mkdir('build')
	DirExplorer.cd_build()
	call_cmake()

DirExplorer.cd_core_v1()
DirExplorer.cd_build()
call_make()
copy_file_in_parent_dir('YololTranslator.exe')

# Compile core v2 and copy the shared library at the right place
current_step = 'Core v2'
log('Setup')
if args.cmake:
	DirExplorer.cd_core_v1()
	os.mkdir('build')
	DirExplorer.cd_build()
	call_cmake()
DirExplorer.cd_core_v2()
DirExplorer.cd_build()
call_make()
copy_file_in_parent_dir('libYololTranslator.so')

# Start the discord bot
current_step = 'Discord'
log('Setup')
DirExplorer.cd_discord()
if args.install:
	call_npm_install()
call_deploy()


# Start the web module
current_step = 'Web'
log('Setup')
DirExplorer.cd_web()
if args.install:
	call_npm_install()
call_deploy()

DirExplorer.cd_base()