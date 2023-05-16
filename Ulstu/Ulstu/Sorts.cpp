#include <iostream>

void BubbleSort(int arr[], int n);

void SelectionSort(int arr[], int n);

void InsertionSort(int arr[], int n);

int Partition(int arr[], int low, int high);
void QuickSort(int arr[], int low, int high);

void Merge(int arr[], int l, int m, int r);
void MergeSort(int arr[], int l, int r);

void ShellSort(int arr[], int n);

void Heapify(int arr[], int n, int i);
void HeapSort(int arr[], int n);

int main()
{
    int n;

    std::cin >> n;

    int* arr = (int*)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++)
    {
        std::cout << "Введите число " << i << ": ";
        std::cin >> arr[i];
    }

    for (int i = 0; i < 10; i++)
    {
        std::cout << arr[i];
        std::cout << " ";
    }

    BubbleSort(arr, 10);

    for (int i = 0; i < 10; i++)
    {
        std::cout << arr[i];
        std::cout << " ";
    }
}

#pragma region Пузырьковая сортировка

void BubbleSort(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

#pragma endregion

#pragma region Сортировка выбором

void SelectionSort(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int minIndex = i;

        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        std::swap(arr[minIndex], arr[i]);
    }
}

#pragma endregion

#pragma region Сортировка вставками

void InsertionSort(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

#pragma endregion

#pragma region Быстрая сортировка

int Partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void QuickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = Partition(arr, low, high);
        QuickSort(arr, low, pi - 1);
        QuickSort(arr, pi + 1, high);
    }
}

#pragma endregion

#pragma region Сортировка слиянием

void Merge(int arr[], int l, int m, int r)
{
    const int n1 = m - l + 1;
    const int n2 = r - m;

    int* L = (int*)calloc(n1, sizeof(int));
    int* R = (int*)calloc(n2, sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0;
    int j = 0;
    int k = l;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }

        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void MergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        MergeSort(arr, l, m);
        MergeSort(arr, m + 1, r);
        Merge(arr, l, m, r);
    }
}

#pragma endregion

#pragma region Сортировка Шелла

void ShellSort(int arr[], int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i += 1)
        {
            int temp = arr[i];
            int j;

            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];

            arr[j] = temp;
        }
    }
}

#pragma endregion

#pragma region Сортировка кучей

void Heapify(int arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i)
    {
        std::swap(arr[i], arr[largest]);
        Heapify(arr, n, largest);
    }
}

void HeapSort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        Heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--)
    {
        std::swap(arr[0], arr[i]);
        Heapify(arr, i, 0);
    }
}

#pragma endregion
