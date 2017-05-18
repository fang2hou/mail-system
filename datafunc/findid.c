/*
 * Data Function - FindID
 * 
 * Author: Zhou Fang
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
 * ╔═╗╦╔╗╔╔╦╗  ┬┌┬┐
 * ╠╣ ║║║║ ║║  │ ││
 * ╚  ╩╝╚╝═╩╝  ┴─┴┘
 * Author: Zhou Fang
 * Last Update: Zhou Fang @ 5/1/2017
 * Use 3 methods to find the unique id.
 * @param {data*} startData where the data start.
 * @param {data*} endData where the data end.
 * @param {int} dataNumber to display the number of data.
 * @param {char*} subTitle the sub title which will be displayed.
 * @return {int} operateCode no found -> 0, found -> else.
 */
int FindID(data *startData, data *endData, int dataNumber, char *subTitle)
{
    int loopIndex = 0;
    int searchMode = 0;// 1-Name 2-Mail 3-Group
    int resultCounter = 0;
    int isMatch = 0;
    int result = 0;
    data *tempStartData;
    data *tempEndData;
    data *currentData;
    char keyword[50];

    //init
    tempEndData = malloc(sizeof(data));
    tempStartData = tempEndData;

    currentData = startData;
    ClearScreen();
    ShowTitle();
    printf("==[%s]=======================\n", subTitle);
    printf("= 今のデータ数：%d\n", dataNumber);
    printf("= 1 名前で検索\n");
    printf("= 2 メールアドレスで検索\n");
    printf("= 3 グループで検索\n");
    printf("= 4 すべてのデータを表示（A〜Z順）\n");
    printf("= 0 戻る\n>");

    FlushBuffer();
    scanf("%d", &searchMode);

    // make sure the correct mode code has been inputted
    while (searchMode < -1 || searchMode > 4) {
        printf("入力したモードは存在しません、もう一度入力してください。\n");
        FlushBuffer();
        scanf("%d", &searchMode);
    }

    // if the mode code is 0, quit immediately
    if (searchMode == 0)
    {
        return 0;
    }
    else if(searchMode == 4)
    {
        ClearScreen();
        ShowTitle();
        printf("==[%s]=======================\n", subTitle);
        DataReadAll(startData, endData);
        printf("\n= 0 戻る\n>");

        FlushBuffer();
        scanf("%d", &searchMode);

        while (searchMode != 0)
        {
            printf("入力したモードは存在しません、もう一度入力してください。\n");
            FlushBuffer();
            scanf("%d", &searchMode);
        }
        result = FindID(startData, endData, dataNumber, subTitle);
        return result;
    }
    printf("\nキーワードを入力してください\n>");

    // get the keyword (length < 128)
    FlushBuffer();
    fgets(keyword, 128, stdin);
    StringInLine(keyword);

    ClearScreen();
    ShowTitle();
    printf("==[%s]======================\n", subTitle);

    for (loopIndex = 0; loopIndex < dataNumber; currentData = currentData->next)
    {
        isMatch = 0;

        loopIndex++;

        switch(searchMode)
        {
            default:
                break;
            case 1:
                if (strstr(currentData->name, keyword))
                {
                    isMatch = 1;
                }
                break;
            case 2:
                if (strstr(currentData->mail, keyword))
                {
                    isMatch = 1;
                }
                break;
            case 3:
                if (strstr(currentData->group, keyword))
                {
                    isMatch = 1;
                }
                break;
        }

        if (isMatch == 1)
        {

            if (resultCounter > 0)
            {
                tempEndData->next = malloc(sizeof(data));
                tempEndData = tempEndData->next;
            }
            *tempEndData = *currentData;
            tempEndData->next = NULL;
            resultCounter++;
            DataRead(startData, endData, currentData->id);
        }
    }

    // if there is just one datum has been found, let user lock the result.
    printf("\n= 結果数：%d\n", resultCounter);
    if (resultCounter == 1)
    {
        printf("= 1 確定\n");
    }
    else if (resultCounter > 1)
    {
        printf("= 1 他のキーワードでデータを特定\n");
    }
    printf("= 8 A~Zで表示\n");
    printf("= 9 他のキーワードで絞り込む\n");
    printf("= 0 戻る\n>");

    // get modecode from standard input
    FlushBuffer();
    scanf("%d", &searchMode);

    // make sure the mode code
    if (resultCounter == 0)
    {
        while (searchMode != 9 && searchMode != 0 && searchMode != 8)
        {
            printf("入力したモードは存在しません、もう一度入力してください。\n");
            FlushBuffer();
            scanf("%d", &searchMode);
        }
    }
    else if (resultCounter >= 1)
    {
        while (searchMode != 1 && searchMode != 9 && searchMode != 0 && searchMode != 8)
        {
            printf("入力したモードは存在しません、もう一度入力してください。\n");
            FlushBuffer();
            scanf("%d", &searchMode);
        }
    }

    // return the unique id or call FindID one more time
    switch (searchMode)
    {
        default:
            break;
        case 1:
            if (resultCounter == 1)
            {
                result = tempEndData->id;
            }
            else
            {
                result = FindID(tempStartData, tempEndData, resultCounter, subTitle);
            }
            break;
        case 8:
            DataReadAll(tempStartData, tempEndData);
            printf("\n= 0 戻る\n>");
            FlushBuffer();
            scanf("%d", &searchMode);

            while (searchMode != 0)
            {
                FlushBuffer();
                scanf("%d", &searchMode);
            }
            result = 0;
            break;
        case 9:
            result = FindID(startData, endData, dataNumber, subTitle);
            break;
        case 0:
            result = 0;
            break;
    }

    FreeData(tempStartData, tempEndData);
    return result;
}