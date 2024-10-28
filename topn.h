#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Student
{
	string name;
	string id;
	double score;	// 成绩为0.5的倍数

	Student() = default;
	Student(double s) :score(s) {}
	Student(const string& n, const string& i, double s) :name(n), id(i), score(s) {}
	Student(const Student& other) :name(other.name), id(other.id), score(other.score) {}
};

/*
* 关于top_n问题综合考虑最好的方法是堆排序，即创建一个有n个元素的最小堆，遍历序列将每个元素与堆顶元素比较，
* 如果堆顶元素小与序列中的元素，就用序列元素替换堆顶元素，再调整堆。这种方法的时间复杂度为O(nlogm)，n为序列元素个数，m为堆的大小
* 
* 但是考虑到这题需要尽可能地快，在优先考虑速度的情况下使用桶排序，这样会牺牲一些空间但是时间复杂度降低到O(n)。
*/

/**
 * @param students 要排序的学生数据
 * @param n 选取前n个
 * @return 排序的结果
 */
vector<Student> top_n(vector<Student>& students, int n)
{
	// 先找到最大值和最小值
	double max_score = -9999.0, min_score = 9999.0;
	for (const auto& student : students)
	{
		max_score = max(max_score, student.score);
		min_score = min(min_score, student.score);
	}
	// 根据二者的差来创建数组，成绩为0.5的倍数所以创建的容量大小为差的双倍，1~2之间有1.0 1.5 2.0三个数，所以结果再加1
	vector<vector<Student>> arr((int)((max_score - min_score) * 2 + 1), vector<Student>{});
	// 遍历students，将每个student按照成绩存储到对应下标中
	for (const auto& student : students)
	{
		arr[(int)((student.score - min_score) * 2)].emplace_back(student);
	}
	// ans存放结果
	vector<Student> ans;
	// 倒序遍历，找前n个符合条件的
	int k = arr.size() - 1;
	while (true)
	{
		// 如果当前的arr存放的成绩数量大于0，则遍历arr[k]，将其中所有的student放到结果中
		if (arr[k].size() > 0)
		{
			for (auto& stu : arr[k])
			{
				ans.emplace_back(stu);
				// 若ans的数量已经为n，则直接返回
				if (ans.size() == n)
				{
					return ans;
				}
			}
		}
		k--;
	}
}