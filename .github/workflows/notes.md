# Retrieve TAG info (seems to work in PIO terminal (Powershell) but not on the older windows CMD terminal)
* get the latest tag from all branches (normally tags and releases are only done on main) : git describe --tags $(git rev-list --tags --max-count=1)
* update local with remote (needed to be sure to get the latest tags) : git remote update
* latest tag on main : git describe --tag $(git rev-parse --verify refs/remotes/origin/main)


v1.0.0-19-gefb23e2




C:\msys64\usr\bin


# https://github.com/marketplace/actions/release-please-action
# https://www.conventionalcommits.org/en/v1.0.0/
# https://docs.github.com/en/repositories/releasing-projects-on-github/automatically-generated-release-notes
# https://docs.github.com/en/actions
# https://naereen.github.io/badges/

# take input from 2nd character
cut -c 2-

# split by delimitor and select n-th field
cut -d '.' -f<n>



     


#            $currentversion = $(git describe --tag $(git rev-parse --verify refs/remotes/origin/main))
            declare -i currentmajorversion=$(git describe --tag $(git rev-parse --verify refs/remotes/origin/main) | cut -c 2- | cut -d'.' -f1)
            echo "currentmajorversion=$currentmajorversion"
            declare -i nextmajorversion=$currentmajorversion+1
            echo "nextmajorversion=$nextmajorversion"


#            $currentminorversion = $(git describe --tag $(git rev-parse --verify refs/remotes/origin/main) | cut -c 2- | cut -d'.' -f2)
#            $currentpatchversion = $(git describe --tag $(git rev-parse --verify refs/remotes/origin/main) | cut -c 2- | cut -d'.' -f3)
#            echo "currentversion=$currentversion" >> $GITHUB_OUTPUT
#            echo "currentmajorversion=$currentmajorversion" >> $GITHUB_OUTPUT
#echo "currentminorversion=$currentminorversion" >> $GITHUB_OUTPUT
#            echo "currentpatchversion=$currentpatchversion" >> $GITHUB_OUTPUT

            #echo "Current Major version : ${{ steps.getalltags.outputs.currentmajorversion }}"

#            echo "currentversion=$(git describe --tag $(git rev-parse --verify refs/remotes/origin/main))" >> $GITHUB_OUTPUT
            #echo "currentmajorversion=$(git describe --tag $(git rev-parse --verify refs/remotes/origin/main) | cut -c 2- | cut -d'.' -f1)" >> $GITHUB_OUTPUT
            #echo "currentminorversion=$(git describe --tag $(git rev-parse --verify refs/remotes/origin/main) | cut -c 2- | cut -d'.' -f2)" >> $GITHUB_OUTPUT
            #echo "currentpatchversion=$(git describe --tag $(git rev-parse --verify refs/remotes/origin/main) | cut -c 2- | cut -d'.' -f3)" >> $GITHUB_OUTPUT


#            echo "nextMinor=$(git describe --tag $(git rev-parse --verify refs/remotes/origin/main) | cut -d'_' -f1-3 | awk -F'_' '{print $1"_"$2+1"_"$3-$3}')" >> $GITHUB_OUTPUT
#            echo "nextPatch=$(git describe --tag $(git rev-parse --verify refs/remotes/origin/main) | cut -d'_' -f1-3 | awk -F'_' '{print $1"_"$2"_"$3+1}')" >> $GITHUB_OUTPUT
  



unittest:
      name: run all unit tests
      runs-on: ubuntu-latest
      steps:
        - name: CheckOut repository
          uses: actions/checkout@v3

        - name: Enable cache
          uses: actions/cache@v3
          with:
            path: |
              ~/.cache/pip
              ~/.platformio/.cache
            key: ${{ runner.os }}-pio

        - name: Install Python 3.9
          uses: actions/setup-python@v4
          with:
            python-version: '3.9'

        - name: Install PlatformIO Core
          run: pip install --upgrade platformio

        - name: Run all generic unit tests
          run: pio test -e all_generic_unittests




    release:
      name: release a new version
      needs: build
      runs-on: ubuntu-latest
      permissions:
        contents: write
        pull-requests: write
      steps:
        - name: Google's Release Please
          uses: google-github-actions/release-please-action@v3
          with:
            package-name: release-please-action
            release-type: simple
        - name: Upload Release Package
          if: ${{ steps.release.outputs.release_created }}
          env:
            GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
          run: gh release upload ${{ steps.release.outputs.tag_name }} .pio/build/production/firmware.bin






              build:
      name: build a binary
      needs: versioning
      runs-on: ubuntu-latest
      steps:
        - name: CheckOut repository
          uses: actions/checkout@v3

        - name: Enable cache
          uses: actions/cache@v3
          with:
            path: |
              ~/.cache/pip
              ~/.platformio/.cache
            key: ${{ runner.os }}-pio

        - name: Install Python 3.9
          uses: actions/setup-python@v4
          with:
            python-version: '3.9'

        - name: Install PlatformIO Core
          run: pip install --upgrade platformio

        - name: Build
          run: pio run -e production

        - name: Archive Production results
        uses: actions/upload-artifact@v3
        with:
          name: ${{ needs.versioncheck.outputs.nextversiontag }}.bin
          path: .pio/build/mumo_v2x_pcb/firmware.bin
          if-no-files-found: error



        - name: Version Test
          id: versiontester
          run: |
            echo "Current latest version : ${{ steps.getalltags.outputs.currentversion }}"
            echo "Current Major version : ${{ steps.getalltags.outputs.currentmajorversion }}"
            echo "Current Minor version : ${{ steps.getalltags.outputs.currentminorversion }}"
            echo "Current Patch version : ${{ steps.getalltags.outputs.currentpatchversion }}"
  
        - name: when running on main branch check commit title
          id: selectversion
          run: |
            if [ "${{ github.ref }}" == "refs/heads/main" ]; then
              echo "Running on main branch"
              echo "Checking commit title"
              echo "Commit title: ${{ github.event.head_commit.message }}"
              if [[ "${{ github.event.head_commit.message }}" == *"major"* ]]; then
                echo "major version bump"
                echo "nextversiontag=${{ steps.getalltags.outputs.nextMajor }}" >> $GITHUB_OUTPUT
              elif [[ "${{ github.event.head_commit.message }}" == *"minor"* ]]; then
                echo "minor version bump"
                echo "nextversiontag=${{ steps.getalltags.outputs.nextMinor }}" >> $GITHUB_OUTPUT
              else
                echo "No version bump specified"
                echo "nextversiontag=${{ steps.getalltags.outputs.nextPatch }}" >> $GITHUB_OUTPUT
              fi
            else
              echo "Not running on main branch"
              echo "nextversiontag=${{ steps.getalltags.outputs.fullversiontag }}" >> $GITHUB_OUTPUT
            fi

  