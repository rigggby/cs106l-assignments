#include "user.h"

/**
 * Creates a new User with the given name and no friends.
 */
User::User(const std::string& name)
  : _name(name)
  , _friends(nullptr)
  , _size(0)
  , _capacity(0)
{
}

User::User(const User& other)
  : _name(other.get_name())
  , _friends(new std::string[other.capacity()])
  , _size(other.size())
  , _capacity(other.capacity()) 
{
  for (size_t i = 0; i < other.size(); ++i) {
    _friends[i] = other._friends[i];
  }
}

User& User::operator=(const User& other) {
  if (this == &other) return *this;
  this->_name = other.get_name();
  delete[] this->_friends;
  this->_friends = new std::string[other.capacity()];
  this->_size = other.size();
  this->_capacity = other.capacity();
  for (size_t i = 0; i < other.size(); ++i) {
    this->_friends[i] = other._friends[i];
  }
  return *this;
}

User::~User()
{
  delete[] _friends;
}

/**
 * Adds a friend to this User's list of friends.
 * @param name The name of the friend to add.
 */
void
User::add_friend(const std::string& name)
{
  if (_size == _capacity) {
    _capacity = 2 * _capacity + 1;
    std::string* newFriends = new std::string[_capacity];
    for (size_t i = 0; i < _size; ++i) {
      newFriends[i] = _friends[i];
    }
    delete[] _friends;
    _friends = newFriends;
  }

  _friends[_size++] = name;
}

/**
 * Returns the name of this User.
 */
std::string
User::get_name() const
{
  return _name;
}

/**
 * Returns the number of friends this User has.
 */
size_t
User::size() const
{
  return _size;
}

size_t User::capacity() const {
  return _capacity;
}

/**
 * Sets the friend at the given index to the given name.
 * @param index The index of the friend to set.
 * @param name The name to set the friend to.
 */
void User::set_friend(size_t index, const std::string& name)
{
  _friends[index] = name;
}

std::ostream& operator<<(std::ostream& os, const User& user)
{
  os << "User(name=" << user.get_name() << ", friends=[";
  for (size_t i = 0; i < user.size(); ++i) {
    if (i > 0) os << ", ";
    os << user._friends[i];
  }
  os << "])";
  return os;
}

User& User::operator+=(User& rhs) {
  if (this == &rhs) return *this;
  this->add_friend(rhs.get_name());
  rhs.add_friend(this->get_name());
  return *this;
}

bool User::operator<(const User& rhs) const {
  return this->get_name() < rhs.get_name();
}
