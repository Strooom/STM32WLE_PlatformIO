# Retrieve TAG info (seems to work in PIO terminal (Powershell) but not on the older windows CMD terminal)
* get the latest tag from all branches (normally tags and releases are only done on main) : git describe --tags $(git rev-list --tags --max-count=1)
* update local with remote (needed to be sure to get the latest tags) : git remote update
* latest tag on main : git describe --tag $(git rev-parse --verify refs/remotes/origin/main)


# https://github.com/marketplace/actions/release-please-action
# https://www.conventionalcommits.org/en/v1.0.0/
# https://docs.github.com/en/repositories/releasing-projects-on-github/automatically-generated-release-notes
# https://docs.github.com/en/actions
# https://naereen.github.io/badges/

        
  
          #export PLATFORMIO_BUILD_FLAGS="'-DNEXT_VERSION=\"${{ needs.versioning.outputs.nextversion }}-MCU4M-PROD\"'"
  
  
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


  