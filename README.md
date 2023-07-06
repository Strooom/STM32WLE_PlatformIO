![example workflow](https://github.com/strooom/STM32WLE_PlatformIO/actions/workflows/testbuildrelease.yml/badge.svg)
[![codecov](https://codecov.io/gh/Strooom/STM32WLE_PlatformIO/branch/develop/graph/badge.svg?token=IC37G15NC9)](https://codecov.io/gh/Strooom/STM32WLE_PlatformIO)

# STM32WLE_PlatformIO
Developing for STM32WLE5 using PlatformIO io STM32CubeIDE
This repository is actually a testbed for getting the development environment right

* builds and unittesting locally on your desktop
* build and unittesting in github actions
* the results of unittesting are uploaded to Codecov for easy inspection of the code coverage
* automatic versioning :
  * when building locally, or on a development branch, the version is the last released version plus the commit hash, eg v1.0.3-73ca67f
  * when building in the cloud on development branch, same as local
  * when merging into main branch : using SemVer where the numbers automatically increase depending on the merge commit message (major, minor or other)
* the version-string and a build-timestamp are available in the source code via an include file
* after the workflow has run, a binary (eg. v1_0_3-73ca67f.bin) is attached to the workflow run
* when the workflow runs for a merge into main, a release is created, and the bin file is attached to the release.

