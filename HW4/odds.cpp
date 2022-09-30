void removeOdds(vector<int>& v)
{
	for (unsigned int i = 0; i < v.size(); i++)
	{
		if (v[i] % 2 == 1)
		{
			v.erase(v.begin() + i);
			i--;
		}
	}
}