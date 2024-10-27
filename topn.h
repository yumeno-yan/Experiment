#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Student
{
	string name;
	string id;
	double score;	// �ɼ�Ϊ0.5�ı���

	Student() = default;
	Student(double s) :score(s) {}
	Student(const string& n, const string& i, double s) :name(n), id(i), score(s) {}
	Student(const Student& other) :name(other.name), id(other.id), score(other.score) {}
};

/**
 * @param students Ҫ�����ѧ������
 * @param n ѡȡǰn��
 * @return ����Ľ��
 */
vector<Student> top_n(vector<Student>& students, int n)
{
	// ���ҵ����ֵ����Сֵ
	double max_score = -9999.0, min_score = 9999.0;
	for (const auto& student : students)
	{
		max_score = max(max_score, student.score);
		min_score = min(min_score, student.score);
	}
	// ���ݶ��ߵĲ����������飬�ɼ�Ϊ0.5�ı������Դ�����������СΪ���˫����1~2֮����1.0 1.5 2.0�����������Խ���ټ�1
	vector<vector<Student>> arr((int)((max_score - min_score) * 2 + 1), vector<Student>{});
	// ����students����ÿ��student���ճɼ��洢����Ӧ�±���
	for (const auto& student : students)
	{
		arr[(int)((student.score - min_score) * 2)].emplace_back(student);
	}
	// ans��Ž��
	vector<Student> ans;
	// �����������ǰn������������
	int k = arr.size() - 1;
	while (true)
	{
		// �����ǰ��arr��ŵĳɼ���������0�������arr[k]�����������е�student�ŵ������
		if (arr[k].size() > 0)
		{
			for (auto& stu : arr[k])
			{
				ans.emplace_back(stu);
				// ��ans�������Ѿ�Ϊn����ֱ�ӷ���
				if (ans.size() == n)
				{
					return ans;
				}
			}
		}
		k--;
	}
}