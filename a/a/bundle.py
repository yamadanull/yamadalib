import subprocess
import sys
import re
import io
import os
import datetime

included_files = set()

def read_file(path):
	try:
		with open(path, 'r', encoding='utf-8') as f:
			return f.read()
	except:
		return None

def resolve_include_path(include, current_dir):
	if include.startswith('<') and include.endswith('>'):
		return None  # ここは None を返して、後でそのまま行を残す
	include = include.strip('"')
	candidate = os.path.join(current_dir, include)
	if os.path.exists(candidate):
		return os.path.abspath(candidate)
	return None

def expand_cpp_includes(path, included_files=None, depth=0):
	if included_files is None: included_files = set()
	if path in included_files: return ''
	included_files.add(path)

	current_dir = os.path.dirname(path)
	content = read_file(path)
	if content is None:
		return f'// Failed to read {path}\n'

	result_lines = []
	lines = content.splitlines()
	include_pattern = re.compile(r'^\s*#\s*include\s+([<"].+[>"])')

	for line in lines:
		# === ここを追加！ ===
		if line.strip() == '#pragma once':
			continue  # 出力に含めずスキップ
		# ====================

		match = include_pattern.match(line)
		if match:
			include_target = match.group(1)
			resolved = resolve_include_path(include_target, current_dir)
			if resolved:
				result_lines.append(f'// Begin include: {include_target}')
				result_lines.append(expand_cpp_includes(resolved, included_files, depth + 1))
				result_lines.append(f'// End include: {include_target}')
			else:
				result_lines.append(line)
		else:
			result_lines.append(line)

	return '\n'.join(result_lines)


sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')

nw = datetime.datetime.now()
print("/**")
print(" * date	 : " + nw.strftime("%Y-%m-%d %H:%M:%S"))
print(" * author : yamadanull")
print(" */")
print()
#print("#define NDEBUG")

lines=expand_cpp_includes("./a.cpp")
