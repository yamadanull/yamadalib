import os
import re
import sys
import datetime

nw = datetime.datetime.now()
print("/**")
print(" * date    : " + nw.strftime("%Y-%m-%d %H:%M:%S"))
print(" * author  : yamadanull")
print(" * library : https://github.com/yamadanull/yamadalib/")
print(" */")
print()
include_pattern = re.compile(r'^\s*#include\s+"([^"]+)"\s*$')

REMOVE_LINES = {
	'#pragma once',
	'#define yamadaDebug',
	'#define yamadaLocal',
}

def expand_file(path, included):
	path = os.path.realpath(path)

	if path in included: return []

	included.add(path)

	try:
		with open(path, encoding='utf-8') as f:
			lines = f.readlines()
	except OSError as e:
		print(f'Error: {path}: {e}', file=sys.stderr)
		return []

	ret = []

	for line in lines:
		stripped = line.strip()
		if stripped in REMOVE_LINES: continue
		match = include_pattern.match(line)
		if match:
			relative_path = match.group(1)
			include_path = os.path.join(
				os.path.dirname(path),
				relative_path
			)

			include_path = os.path.realpath(include_path)

			if include_path not in included:
				ret.append(
					f'// ===== BEGIN INCLUDE: {relative_path} =====\n'
				)
				ret.extend(
					expand_file(include_path, included)
				)
				ret.append(
					f'// ===== END INCLUDE: {relative_path} =====\n'
				)
		else: ret.append(line)
	return ret

def main():
	path = input().strip()
	included = set()
	ret = expand_file(path, included)
	sys.stdout.write(''.join(ret))

if __name__ == '__main__': main()
