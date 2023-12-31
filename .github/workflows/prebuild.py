import subprocess
import os
import sys
import shutil
from datetime import datetime

Import("env")

# determine the build version
latest_release_tag = subprocess.run(["git", "describe", "--tags"], stdout=subprocess.PIPE, text=True) # this should call : git describe --tag $(git rev-parse --verify refs/remotes/origin/main)
latest_release_tag = latest_release_tag.stdout.strip()
print ("\033[93;1;4mLatest Release Tag     : " + latest_release_tag + "\033[0m")

# determine last release version
latest_release_tag_parts = latest_release_tag.split("-")
latest_release_tag_version = latest_release_tag_parts[0]
print ("\033[93;1;4mLatest Release Version : " + latest_release_tag_version + "\033[0m")

# determine current commit hash
current_commit_hash = subprocess.run(["git", "rev-parse", "--short", "HEAD"], stdout=subprocess.PIPE, text=True)
current_commit_hash = current_commit_hash.stdout.strip()
print ("\033[93;1;4mCurrent Commit Hash    : " + current_commit_hash + "\033[0m")

# construct the build version
build_version = latest_release_tag_version + "-" + current_commit_hash
print ("\033[93;1;4mBuild Version          : " + build_version + "\033[0m")

# determine the build timstamp
build_timestamp = datetime.now().strftime("%Y-%b-%d-%H:%M:%S")
print ("\033[93;1;4mBuild Timestamp        : " + build_timestamp + "\033[0m")

# store the results in an include file, so our source code has access to it
include_file = open('include/buildinfo.h', 'w')
include_file.write("// this file is generated by build and continuous integration scripts\n")
include_file.write("#pragma once\n")
include_file.write("#define BUILD_VERSION \"" + build_version + "\"\n")
include_file.write("#define BUILD_TIMESTAMP \"" + build_timestamp + "\"\n")
include_file.close()
