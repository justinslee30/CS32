void removeBad(list<Movie*>& li)
{
	for (list<Movie*>::iterator p = li.begin(); p != li.end(); p++)
	{
		Movie *current = *p;
		if (current->rating() < 50)
		{
			delete current;
			p = li.erase(p);
			p--;
		}
	}
}