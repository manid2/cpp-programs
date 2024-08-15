#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include <bits/stdc++.h>

//=== prototypes

typedef void *gpointer;

struct ChildSetupInfo {
	uid_t uid;
	std::vector<gid_t> gids;
};

bool getUserIdByName(const std::string &name, uid_t &uid);
bool getGroupIdByName(const std::string &name, gid_t &gid);
void child_setup_setuid(gpointer data);

//=== definitions utils.cpp

bool getUserIdByName(const std::string &name, uid_t &uid)
{
	struct passwd *pwd = getpwnam(name.c_str());
	if (pwd == NULL) {
		fprintf(stderr,
		        "reason getpwnam() failed error message: %s\n",
		        strerror(errno));
		return false;
	}
	uid = pwd->pw_uid;
	return true;
}

bool getGroupIdByName(const std::string &name, gid_t &gid)
{
	struct group *grp = getgrnam(name.c_str());
	if (grp == NULL) {
		fprintf(stderr,
		        "reason getgrnam(%s) failed error message: %s\n",
		        name.c_str(), strerror(errno));
		return false;
	}
	gid = grp->gr_gid;
	return true;
}

void child_setup_setuid(gpointer data)
{
	ChildSetupInfo *ch = reinterpret_cast<ChildSetupInfo *>(data);
	uid_t uid = ch ? ch->uid : 0;

	int status = setuid(uid);
	if (status < 0) {
		fprintf(stderr, "reason setuid() failed error message: %s\n",
		        strerror(errno));
		return;
	}

	status = seteuid(uid);
	if (status < 0) {
		fprintf(stderr, "reason seteuid() failed error message: %s\n",
		        strerror(errno));
		return;
	}

	if (ch) {
		status = setgroups(ch->gids.size(), ch->gids.data());
		if (status < 0) {
			fprintf(
			    stderr,
			    "reason setgroups() failed error message: %s\n",
			    strerror(errno));
			return;
		}
	}
}

/// === native app launcher

void fork_process(ChildSetupInfo *child_data)
{
	std::string childUid = "daemon";
	std::vector<std::string> childGroups{"adm", "disk", "adm", "adm", "disk", "disk-no-grp"};
	std::vector<gid_t> childGids;
	for (auto grp : childGroups) {
		gid_t gid = 0;
		if (getGroupIdByName(grp, gid)) childGids.push_back(gid);
	}
	uid_t uid = 0;
	child_data->uid = getUserIdByName(childUid, uid) ? uid : 0;
	child_data->gids = childGids;
}

/// === test helpers

void print(ChildSetupInfo *ch)
{
	using namespace std;

	cout << "uid: " << ch->uid << "\n";
	cout << "gid: ";
	for (auto gid : ch->gids) cout << gid << " ";
	cout << "\n";
}

int main(int, char **)
{
	ChildSetupInfo ch;
	fork_process(&ch);
	print(&ch);

	if (fork() == 0) {
		child_setup_setuid((gpointer)&ch);

		printf("\n\tchild process\n");

		for(;;);
	} else {
		// Old Parent process. The C program will come here
		printf("\nparent process\n");
		for(;;);
	}

	return 0;
}
