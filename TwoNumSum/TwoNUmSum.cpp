#include <stdio.h>

int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    int i, j;
    static int num[2];
    for(i = 0; i < numsSize-1; i++){
        for(j = i + 1; j < numsSize; j++){
            if(nums[i]+nums[j] == target){
               num[0] = i;
               num[1] = j;
               *returnSize = 2; 
               return num;
            }
        }
    }
    
}

int main(int argc, char const *argv[])
{
    int nums[4] = {2,7,11,15};
    int returnsize = 0;
    int *num = twoSum(nums, sizeof(nums), 26, &returnsize);
    
    for(int i = 0; i < 2; i++){
        printf("%d ", num[i]);
    }

    printf("returnsize = %d\n", returnsize);
    return 0;
}
