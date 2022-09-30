void listAll(string path, const File* f)  // two-parameter overload
{
	if (f->files() == nullptr)
	{
		cout << "/" << path << f->name() << endl;
		return;
	}
	if (f->name() != "")
		cout << "/" << path << f->name() << endl;
	for (vector<File*>::const_iterator i = f->files()->begin(); i != f->files()->end(); i++)
	{
		string tempPath;
		if (f->name() != "")
			tempPath = path + f->name() + "/";
		listAll(tempPath, *i);
	}
}