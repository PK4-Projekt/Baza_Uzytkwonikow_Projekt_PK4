#pragma once

#include <QString>
#include <ostream>

class User;
class Feed;

class Address {
    int addressId;
    QString city;
    QString street;
    QString homeNumber;
    QString postalCode;
    QString postOffice;

public:

    Address(int addressId, const QString &city, const QString &street, const QString &homeNumber,
            const QString &postalCode, const QString &postOffice) : addressId(addressId), city(city), street(street),
                                                                    homeNumber(homeNumber), postalCode(postalCode),
                                                                    postOffice(postOffice) {}

    Address(const QString &city, const QString &street, const QString &homeNumber, const QString &postalCode,
            const QString &postOffice) : city(city), street(street), homeNumber(homeNumber), postalCode(postalCode),
                                         postOffice(postOffice) {}

    int getAddressId() const {
        return addressId;
    }

    void setAddressId(int addressId) {
        Address::addressId = addressId;
    }

    const QString &getCity() const {
        return city;
    }

    void setCity(const QString &city) {
        Address::city = city;
    }

    const QString &getStreet() const {
        return street;
    }

    void setStreet(const QString &street) {
        Address::street = street;
    }

    const QString &getHomeNumber() const {
        return homeNumber;
    }

    void setHomeNumber(const QString &homeNumber) {
        Address::homeNumber = homeNumber;
    }

    const QString &getPostalCode() const {
        return postalCode;
    }

    void setPostalCode(const QString &postalCode) {
        Address::postalCode = postalCode;
    }

    const QString &getPostOffice() const {
        return postOffice;
    }

    void setPostOffice(const QString &postOffice) {
        Address::postOffice = postOffice;
    }
};

class ContactGroup {
    int contactGroupId;
    int userId;
    QString name;
    std::vector<User *> users;

public:

    ContactGroup(int contactGroupId, int userId, const QString &name, const std::vector<User *> &users)
            : contactGroupId(contactGroupId), userId(userId), name(name), users(users) {}

    ContactGroup(int contactGroupId, int userId, const QString &name) : contactGroupId(contactGroupId), userId(userId),
                                                                        name(name) {}

    virtual ~ContactGroup() {
        for(unsigned long long i = 0; i < users.size(); i++) {
            delete users[i];
        }
    }

    const std::vector<User *> &getUsers() const {
        return users;
    }

    void setUsers(const std::vector<User *> &users) {
        ContactGroup::users = users;
    }

    int getContactGroupId() const {
        return contactGroupId;
    }

    void setContactGroupId(int contactGroupId) {
        ContactGroup::contactGroupId = contactGroupId;
    }

    int getUserId() const {
        return userId;
    }

    void setUserId(int userId) {
        ContactGroup::userId = userId;
    }

    const QString &getName() const {
        return name;
    }

    void setName(const QString &name) {
        ContactGroup::name = name;
    }
};

class Email {
    int emailId;
    QString email;
    QString comment;
public:
    Email(int emailId, const QString &email, const QString &comment) : emailId(emailId), email(email),
                                                                       comment(comment) {}

    int getEmailId() const {
        return emailId;
    }

    void setEmailId(int emailId) {
        Email::emailId = emailId;
    }

    const QString &getEmail() const {
        return email;
    }

    void setEmail(const QString &email) {
        Email::email = email;
    }

    const QString &getComment() const {
        return comment;
    }

    void setComment(const QString &comment) {
        Email::comment = comment;
    }
};

class Phone {
    int phoneId;
    QString phone;
    QString comment;

public:
    Phone(int phoneId, const QString &phone, const QString &comment) : phoneId(phoneId), phone(phone),
                                                                       comment(comment) {}

    int getPhoneId() const {
        return phoneId;
    }

    void setPhoneId(int phoneId) {
        Phone::phoneId = phoneId;
    }

    const QString &getPhone() const {
        return phone;
    }

    void setPhone(const QString &phone) {
        Phone::phone = phone;
    }

    const QString &getComment() const {
        return comment;
    }

    void setComment(const QString &comment) {
        Phone::comment = comment;
    }
};

class User {
    int userId;
    QString login;
    QString photo;
    QString role;
    QString firstName;
    QString lastName;
    Address *address;
    std::vector<Email *> emails;
    std::vector<Phone *> phones;
    std::vector<ContactGroup *> contactGroups;
    std::vector<Feed *> feed;

public:
    User(int userId, const QString &login, const QString &photo, const QString &role, const QString &firstName,
         const QString &lastName, Address *address, const std::vector<Email *> &emails,
         const std::vector<Phone *> &phones) : userId(userId), login(login), photo(photo), role(role),
                                            firstName(firstName), lastName(lastName), address(address), emails(emails),
                                            phones(phones) {}

    virtual ~User() {
        delete address;
        for(int i = 0; i < emails.size(); i++) {
            delete emails[i];
        }

        for(int i = 0; i < phones.size(); i++) {
            delete phones[i];
        }

        for(int i = 0; i < contactGroups.size(); i++) {
            delete contactGroups[i];
        }

        for(int i = 0; i < feed.size(); i++) {
            delete feed[i];
        }
    }

    int getUserId() const {
        return userId;
    }

    void setUserId(int userId) {
        User::userId = userId;
    }

    const QString &getLogin() const {
        return login;
    }

    void setLogin(const QString &login) {
        User::login = login;
    }

    const QString &getPhoto() const {
        return photo;
    }

    void setPhoto(const QString &photo) {
        User::photo = photo;
    }

    const QString &getRole() const {
        return role;
    }

    void setRole(const QString &role) {
        User::role = role;
    }

    const QString &getFirstName() const {
        return firstName;
    }

    void setFirstName(const QString &firstName) {
        User::firstName = firstName;
    }

    const QString &getLastName() const {
        return lastName;
    }

    void setLastName(const QString &lastName) {
        User::lastName = lastName;
    }

    Address *getAddress() const {
        return address;
    }

    void setAddress(Address *address) {
        User::address = address;
    }

    const std::vector<Email *> &getEmails() const {
        return emails;
    }

    void setEmails(const std::vector<Email *> &emails) {
        User::emails = emails;
    }

    const std::vector<Phone *> &getPhones() const {
        return phones;
    }

    void setPhones(const std::vector<Phone *> &phones) {
        User::phones = phones;
    }

    const std::vector<ContactGroup *> &getContactGroups() const {
        return contactGroups;
    }

    void setContactGroups(const std::vector<ContactGroup *> &contactGroups) {
        User::contactGroups = contactGroups;
    }

    const std::vector<Feed *> &getFeed() const {
        return feed;
    }

    void setFeed(const std::vector<Feed *> &feed) {
        User::feed = feed;
    }

    QString toQString() {
        return login + " | " + firstName + " " + lastName;
    }

};

class Feed {
    int feedId;
    int userId;
    int *contactShareId;
    QString content;
    QString date;
    int authorUserId;
public:
    Feed(int feedId, int userId, int *contactShareId, const QString &content, const QString &date, int authorUserId)
            : feedId(feedId), userId(userId), contactShareId(contactShareId), content(content), date(date),
              authorUserId(authorUserId) {}

    virtual ~Feed() {
        delete contactShareId;

    }

    int getFeedId() const {
        return feedId;
    }

    void setFeedId(int feedId) {
        Feed::feedId = feedId;
    }

    int getUserId() const {
        return userId;
    }

    void setUserId(int userId) {
        Feed::userId = userId;
    }

    int *getContactShareId() const {
        return contactShareId;
    }

    void setContactShareId(int *contactShareId) {
        Feed::contactShareId = contactShareId;
    }

    const QString &getContent() const {
        return content;
    }

    void setContent(const QString &content) {
        Feed::content = content;
    }

    const QString &getDate() const {
        return date;
    }

    void setDate(const QString &date) {
        Feed::date = date;
    }

    int getAuthorUserId() const {
        return authorUserId;
    }

    void setAuthorUserId(int authorUserId) {
        Feed::authorUserId = authorUserId;
    }
};

class ContactShare {
    int contactShareId;
    int srcUserId;
    int desUserId;
    int contactGroupId;

public:
    ContactShare(int contactShareId, int srcUserId, int desUserId, int contactGroupId) : contactShareId(contactShareId),
                                                                                         srcUserId(srcUserId),
                                                                                         desUserId(desUserId),
                                                                                         contactGroupId(
                                                                                                 contactGroupId) {}

    int getContactShareId() const {
        return contactShareId;
    }

    void setContactShareId(int contactShareId) {
        ContactShare::contactShareId = contactShareId;
    }

    int getSrcUserId() const {
        return srcUserId;
    }

    void setSrcUserId(int srcUserId) {
        ContactShare::srcUserId = srcUserId;
    }

    int getDesUserId() const {
        return desUserId;
    }

    void setDesUserId(int desUserId) {
        ContactShare::desUserId = desUserId;
    }

    int getContactGroupId() const {
        return contactGroupId;
    }

    void setContactGroupId(int contactGroupId) {
        ContactShare::contactGroupId = contactGroupId;
    }
};

class Invitation {
    int invitationId;
    QString date;
    int contactGroupId;
    int userId;
public:
    Invitation(int invitationId, const QString &date, int contactGroupId, int userId) : invitationId(invitationId),
                                                                                        date(date),
                                                                                        contactGroupId(contactGroupId),
                                                                                        userId(userId) {}

    int getInvitationId() const {
        return invitationId;
    }

    void setInvitationId(int invitationId) {
        Invitation::invitationId = invitationId;
    }

    const QString &getDate() const {
        return date;
    }

    void setDate(const QString &date) {
        Invitation::date = date;
    }

    int getContactGroupId() const {
        return contactGroupId;
    }

    void setContactGroupId(int contactGroupId) {
        Invitation::contactGroupId = contactGroupId;
    }

    int getUserId() const {
        return userId;
    }

    void setUserId(int userId) {
        Invitation::userId = userId;
    }
};
