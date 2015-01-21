#ifndef DATABASE_INCLUDED
#define DATABASE_INCLUDED

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

template<typename T>
class Database {
public:

	Database();
	Database(string fileName);
	Database(string fileName, vector<T> rows);

	bool create(T newValue);
	T get(int index);
	vector<T> getAll();
	bool update(int index, T newValue);
	bool remove(int index);
	void addRow(T item);

	int getRowsCount();
	const string getFileName() const;
	void setFileName(const string& fileName);
	const vector<T> getRows() const;
	void setRows(const vector<T>& rows);
	bool isModified() const;

	bool operator==(const Database<T>& other) {
		if (fileName != other.getFileName())
			return false;

		vector<T> otherRows = other.getRows();
		if (rows.size() != otherRows.size())
			return false;

		for (int i = 0, j = rows.size(); i < j; i++)
			if (rows[i] != otherRows[i])
				return false;

		return true;
	}

	bool operator!=(const Database<T>& other) {
		return !(*this == other);
	}

	void setModified(bool modified) {
		this->modified = modified;
	}

protected:
	bool modified;
	string fileName;
	vector<T> rows;

	bool isIndexIncorrect(int index) {
		return index < 0 || this->rows.size() <= index;
	}

};

/*
 * IMPLEMENTATIONS
 */

template<typename T>
inline Database<T>::Database() {
	this->modified = false;
}

template<typename T>
inline Database<T>::Database(string fileName) {
	this->fileName = fileName;
	this->modified = false;
}

template<typename T>
inline Database<T>::Database(string fileName, vector<T> rows) {
	this->fileName = fileName;
	this->rows = rows;
	this->modified = false;
}

template<typename T>
inline bool Database<T>::create(T newValue) {
	this->rows.push_back(newValue);
	return true;
}

template<typename T>
inline T Database<T>::get(int index) {
	return this->rows[index];
}

template<typename T>
inline vector<T> Database<T>::getAll() {
	vector<T> copy;
	copy(rows.begin(), rows.end(), copy.begin());

	return copy;
}

template<typename T>
inline bool Database<T>::update(int index, T newValue) {
	if (!this->remove(index))
		return false;

	this->rows.insert(rows.begin() + index, newValue);
	this->modified = true;

	return true;
}

template<typename T>
inline bool Database<T>::remove(int index) {
	if (this->isIndexIncorrect(index))
		return false;

	this->rows.erase(rows.begin() + index);
	this->modified = true;

	return true;
}

template<typename T>
inline int Database<T>::getRowsCount() {
	return rows.size();
}

template<typename T>
inline const string Database<T>::getFileName() const {
	return fileName;
}

template<typename T>
inline void Database<T>::setFileName(const string& fileName) {
	this->fileName = fileName;
	this->modified = true;
}

template<typename T>
inline const vector<T> Database<T>::getRows() const {
	vector<T> temp;

	for (int i = 0, j = rows.size(); i < j; i++)
		temp.push_back(rows[i]);

	return temp;
}

template<typename T>
inline void Database<T>::setRows(const vector<T>& rows) {
	this->rows = rows;
	this->modified = true;
}

template<typename T>
inline void Database<T>::addRow(T item) {
	rows.push_back(item);
	this->modified = true;
}

template<typename T>
inline bool Database<T>::isModified() const {
	return modified;
}

#endif
