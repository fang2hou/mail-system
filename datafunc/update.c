/*
 * Data Function - Update
 * 
 * Author: Atsushi Hasegawa
 *
 * Copyright (C) 2017 Group F Mail System Project
 *
 * Licensed under the GNU General Public License, Version 3.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      https://www.gnu.org/licenses/gpl-3.0.en.html
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * ╦ ╦╔═╗╔╦╗╔═╗╔╦╗╔═╗  ┬ ┬┬
 * ║ ║╠═╝ ║║╠═╣ ║ ║╣   │ ││
 * ╚═╝╩  ═╩╝╩ ╩ ╩ ╚═╝  └─┘┴
 * Author: Atsushi Hasegawa
 * Last Update: Zhou Fang @ 5/7/2017
 * Help user to find and update saved data.
 * @param {data*} startData where the data start.
 * @param {data*} endData where the data end.
 * @param {int} dataNumber to display the number of data.
 * @param {backupdata*} backupData The pointer show where the backup datum is.
 * @param {int*} changeCounter The global change counter.
 */
void DataUpdateUI(data *startData, data *endData, int dataNumber, backupdata *backupData, int *changeCounter)
{
    int dataID = 0;
    int exitCode = 0;
    data *editedData;
    dataID = FindID(startData, endData, dataNumber, "既存のデータのUPDATE");

    editedData = (data *)calloc(1, sizeof(data));

    if (dataID != 0)
    {
        do{
            ClearScreen();
            ShowTitle();
            printf("==[%s]======================\n", "既存のデータのUPDATE");
            DataReadEdited(startData, endData, editedData, dataID);
            printf("===================================\n");
            printf("= 1 名前の変更\n");
            printf("= 2 メールアドレスの変更\n");
            printf("= 3 性別の変更\n");
            printf("= 4 グループの変更\n");
            printf("= 5 保存\n");
            printf("= 0 終了\n>");
            FlushBuffer();
            scanf("%d", &exitCode);
            switch (exitCode){
                default:
                    printf("入力したモードは存在しません、もう一度入力してください。\n");
                    break;
                case 0:
                    break;
                case 1:
                    printf("New name: ");
                    GetString(editedData->name, 30);
                    break;
                case 2:
                    printf("New mail: ");
                    GetString(editedData->mail, 30);
                    break;
                case 3:
                    printf("New sex: ");
                    GetString(editedData->sex, 30);
                    break;
                case 4:
                    printf("New group: ");
                    GetString(editedData->group, 30);
                    break;
                case 5:
                    if( DataUpdate(startData, endData, editedData, dataID, backupData) == 1 )
                    {
                        (*changeCounter)++;
                    }
                    exitCode = 0;
                    break;
            }
        } while (exitCode != 0);
    }

    free(editedData);
}

/**
 * ╦ ╦╔═╗╔╦╗╔═╗╔╦╗╔═╗
 * ║ ║╠═╝ ║║╠═╣ ║ ║╣
 * ╚═╝╩  ═╩╝╩ ╩ ╩ ╚═╝
 * Author: Atsushi Hasegawa
 * Last Update: Zhou Fang @ 5/7/2017
 * update data.
 * @param {data*} startData where the data start.
 * @param {data*} endData where the data end.
 * @param {data*} editedData where the edited data is.
 * @param {int} dataID the unique ID which is datum have.
 * @param {backupdata*} backupData The pointer show where the backup datum is.
 * @return {int} resultCode Success -> 1, Failed -> 0.
 */
int DataUpdate(data *startData, data *endData, data *editedData, int dataID, backupdata *backupData)
{
    data *tempData;
    backupdata *tempBackupData;
    tempBackupData = (backupdata *)calloc(1, sizeof(backupdata));
    tempBackupData->id = dataID;

    for (tempData = startData; tempData != NULL; tempData = tempData->next) {
        if (tempData->id == dataID) {
            if (strlen(editedData->name) != 0)
            {
                strcpy(tempBackupData->name, tempData->name);
                strcpy(tempData->name, editedData->name);
            }

            if (strlen(editedData->mail) != 0)
            {
                strcpy(tempBackupData->mail, tempData->mail);
                strcpy(tempData->mail, editedData->mail);
            }
            if (strlen(editedData->sex) != 0)
            {
                strcpy(tempBackupData->sex, tempData->sex);
                strcpy(tempData->sex, editedData->sex);
            }

            if (strlen(editedData->group) != 0)
            {
                strcpy(tempBackupData->group, tempData->group);
                strcpy(tempData->group, editedData->group);
            }

            break;
        }
    }

    free(backupData);
    backupData = tempBackupData;

    return  1;
}