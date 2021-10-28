def unique_elements(arr1, arr2):
    '''Find unique elements to first arrat which not store in second array with difficult O(N)'''
    k = 0
    len_arr2 = len(arr2)
    for i in arr1:
        for j in arr2[k:]:
            if i < j:
                print(i, end=' ')
                break
            elif i > j:
                k += 1
            else:
                break
        if k >= len_arr2:
            print(i, end=' ')


arr1 = [0, 1, 3, 5, 5, 5, 6, 9, 10, 12, 13, 17, 18, 25]
arr2 = [0, 1, 3, 5, 9, 12, 15, 18, 18, 19]

unique_elements(arr1, arr2)
