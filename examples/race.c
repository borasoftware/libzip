
#include <zip.h>
#include <pthread.h>

void * unzipperTest(void * unused) {
	int error = 0;
	zip_t * archive = zip_open("../../regress/cm-default.zip", ZIP_RDONLY | ZIP_CHECKCONS, &error);

	if (error) {
		fprintf(stderr, "Error opening zip file\n");
	} else {
		zip_discard(archive);
	}

	return NULL;
}

// valgrind --tool=helgrind --vgdb=no --read-inline-info=yes --fair-sched=yes --suppressions=../../examples/helgrind.supp ./race

int main() {
	pthread_t t1;
	pthread_t t2;

	if (pthread_create(&t1, NULL, unzipperTest, NULL)) {
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}

	if (pthread_create(&t2, NULL, unzipperTest, NULL)) {
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}

	if (pthread_join(t1, NULL)) {
		fprintf(stderr, "Error joining thread 1\n");
		return 2;
	}

	if (pthread_join(t2, NULL)) {
		fprintf(stderr, "Error joining thread 2\n");
		return 2;
	}

	return 0;
}
