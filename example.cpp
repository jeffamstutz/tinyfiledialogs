// ======================================================================== //
// Copyright 2019 Intel Corporation                                         //
//                                                                          //
// Licensed under the Apache License, Version 2.0 (the "License");          //
// you may not use this file except in compliance with the License.         //
// You may obtain a copy of the License at                                  //
//                                                                          //
//     http://www.apache.org/licenses/LICENSE-2.0                           //
//                                                                          //
// Unless required by applicable law or agreed to in writing, software      //
// distributed under the License is distributed on an "AS IS" BASIS,        //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. //
// See the License for the specific language governing permissions and      //
// limitations under the License.                                           //
// ======================================================================== //

#include <stdio.h>
#include <string.h>
#include "tinyfiledialogs.h"
int main()
{
  char const *lTmp;
  char const *lTheSaveFileName;
  char const *lTheOpenFileName;
  char const *lTheSelectFolderName;
  char const *lTheHexColor;
  char const *lWillBeGraphicMode;
  unsigned char lRgbColor[3];
  FILE *lIn;
  char lBuffer[1024];
  char lThePassword[1024];
  char const *lFilterPatterns[2] = {"*.txt", "*.text"};

  lWillBeGraphicMode = tinyfd_inputBox("tinyfd_query", NULL, NULL);

  if (lWillBeGraphicMode) {
    strcpy(lBuffer, "graphic mode: ");
  } else {
    strcpy(lBuffer, "console mode: ");
  }

  strcat(lBuffer, tinyfd_response);
  strcpy(lThePassword, "tinyfiledialogs v");
  strcat(lThePassword, tinyfd_version);
  tinyfd_messageBox(lThePassword, lBuffer, "ok", "info", 0);

  if (lWillBeGraphicMode && !tinyfd_forceConsole) {
    tinyfd_forceConsole =
        !tinyfd_messageBox("Hello World",
                           "graphic dialogs [yes] / console mode [no]?",
                           "yesno",
                           "question",
                           1);
  }

  lTmp =
      tinyfd_inputBox("a password box", "your password will be revealed", NULL);

  if (!lTmp)
    return 1;

  /* copy lTmp because saveDialog would overwrites
  inputBox static buffer in basicinput mode */

  strcpy(lThePassword, lTmp);

  lTheSaveFileName = tinyfd_saveFileDialog("let us save this password",
                                           "passwordFile.txt",
                                           2,
                                           lFilterPatterns,
                                           NULL);

  if (!lTheSaveFileName) {
    tinyfd_messageBox("Error", "Save file name is NULL", "ok", "error", 1);
    return 1;
  }

  lIn = fopen(lTheSaveFileName, "w");
  if (!lIn) {
    tinyfd_messageBox(
        "Error", "Can not open this file in write mode", "ok", "error", 1);
    return 1;
  }
  fputs(lThePassword, lIn);
  fclose(lIn);

  lTheOpenFileName = tinyfd_openFileDialog(
      "let us read the password back", "", 2, lFilterPatterns, NULL, 0);

  if (!lTheOpenFileName) {
    tinyfd_messageBox("Error", "Open file name is NULL", "ok", "error", 1);
    return 1;
  }

  lIn = fopen(lTheOpenFileName, "r");

  if (!lIn) {
    tinyfd_messageBox(
        "Error", "Can not open this file in read mode", "ok", "error", 1);
    return (1);
  }
  lBuffer[0] = '\0';
  fgets(lBuffer, sizeof(lBuffer), lIn);
  fclose(lIn);

  tinyfd_messageBox("your password is", lBuffer, "ok", "info", 1);

  lTheSelectFolderName =
      tinyfd_selectFolderDialog("let us just select a directory", NULL);

  if (!lTheSelectFolderName) {
    tinyfd_messageBox("Error", "Select folder name is NULL", "ok", "error", 1);
    return 1;
  }

  tinyfd_messageBox(
      "The selected folder is", lTheSelectFolderName, "ok", "info", 1);

  lTheHexColor = tinyfd_colorChooser(
      "choose a nice color", "#FF0077", lRgbColor, lRgbColor);

  if (!lTheHexColor) {
    tinyfd_messageBox("Error", "hexcolor is NULL", "ok", "error", 1);
    return 1;
  }

  tinyfd_messageBox("The selected hexcolor is", lTheHexColor, "ok", "info", 1);

  return 0;
}
