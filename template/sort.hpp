#ifndef SORT
#define SORT

void bubbleSort(int array[], int length)
{
	for (int i = 0; i < length - 1; i++)
	{
		bool flag = true;
		for (int j = 0; j < length - i - 1; j++)
		{
			if (array[j] > array[j + 1])
			{
				int temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
				flag = false;
			}
		}
		if (flag)
			break;
	}
}

void selectionSort(int array[], int length)
{
	for (int i = 0; i < length; i++)
	{
		int min = i;
		for (int j = i + 1; j < length; j++)
		{
			if (array[j] < array[min])
				min = j;
		}
		int temp = array[min];
		array[min] = array[min];
		array[i] = temp;
	}
}

void insertSort(int array[], int length)
{
	for (int i = 1; i < length; i++)
	{
		if (array[i] < array[i - 1])
		{
			int j = i - 1;
			int temp = array[i];
			while (j >= 0 && temp < array[j])
			{
				array[j + 1] = array[j];
				j--;
			}
			array[j + 1] = temp;
		}
	}
}

void shellSort(int array[], int length)
{
	for (int gap = length; gap >= 1; gap /= 2)
	{
		for (int i = gap; i < length; i += gap)
		{
			int temp = array[i];
			int pre = i - gap;
			while (pre >= 0 && array[pre] > temp)
			{
				array[i] = array[pre];
				pre -= gap;
			}
			array[pre + gap] = temp;
		}
	}
}

void quickSort(int array[], int low, int high)
{
	if (low < high)
	{
		int i = low;
		int j = high;
		int key = array[i];
		while (i < j)
		{
			while (i < j && array[j] >= key)
				j--;
			if (i < j)
				array[i] = array[j];
			while (i < j && array[j] <= key)
				i++;
			if (i < j)
				array[j] = array[i];
		}
		array[i] = key;
		quickSort(array, low, i - 1);
		quickSort(array, i + 1, high);
	}
}

void heapSort(int array[], int length)
{
	int i = length / 2 - 1;
	for (; i >= 0; --i)
	{
		int left = i * 2 + 1;
		int right = i * 2 + 2;
		int j = 0;
		if (right < length)
		{
			array[left] > array[right] ? j = left : j = right;
		}
		else
			j = left;
		if (array[j] > array[i])
		{
			int temp = array[i];
			array[i] = array[j];
			array[j] = temp;
		}
	}
	for (int j = length - 1; j >= 0; j--)
	{
		int temp = array[0];
		array[0] = array[j];
		array[j] = temp;

		int i = j / 2 - 1, n = j;
		for (; i >= 0; --i)
		{
			int left = i * 2 + 1;
			int right = i * 2 + 2;
			int j = 0;
			if (right < n)
			{
				array[left] > array[right] ? j = left : j = right;
			}
			else
				j = left;
			if (array[j] > array[i])
			{
				int temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}
}

void mergeSort(int array[], int left, int right)
{
	if (left > right)
		return;
	int mid = (left + right) / 2;
	mergeSort(array, left, mid - 1);
	mergeSort(array, mid + 1, right);
	merge(array, left, right, mid);
}

void merge(int array[], int left, int mid, int right)
{
	int len = right - left + 1;
	int *temp = new int[len];
	int k = 0;
	int i = left;
	int j = mid + 1;
	while (i <= mid && j <= right)
		temp[k++] = array[i] <= array[j] ? array[i++] : array[j++];
	while (i <= mid)
		temp[k++] = array[i++];
	while (j <= right)
		temp[k++] = array[j++];
	for (int k = 0; k < len; k++)
		array[left++] = temp[k];
}

#endif
