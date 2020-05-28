#include "group.h"

#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Nombre total de tests exécutés. 
int tests_executes = 0;
// Pour chaque test qui réussi, cette variable sera incrémentée de 1.
// Le but est de la garder égale à test_executes.
int tests_reussis = 0;

#define STRINGIZE_(x) #x
#define STRINGIZE(x) STRINGIZE_(x)

// Incrémente le nombre de test exécutés de 1.
// Si le test réussi, incrémente le nombre de tests réussis de 1.
#define TEST(x) tests_executes += 1;    \
				if(x)                   \
				{                       \
					tests_reussis += 1; \
					printf("[SUCCES] ");\
				}                       \
				else                    \
				{                       \
					printf("[ECHEC ] ");\
				}                       \
				printf(STRINGIZE(__FILE__) ", " STRINGIZE(__LINE__) ": " STRINGIZE(x) "\n");

// Compare le contenu de deux fichiers aux chemins a et b avec la commande diff. Incrémente test_reussis si les fichiers sont pareils.
#define TEST_FILE(a, b) tests_executes += 1;                                                \
						{                                                                   \
							int const r = system("diff --text --strip-trailing-cr " a " " b " > /dev/null");    \
							if(!WEXITSTATUS(r))                                             \
							{                                                               \
								tests_reussis += 1;                                         \
								printf("[SUCCES] ");                                        \
							}                                                               \
							else                                                            \
							{                                                               \
								printf("[ECHEC ] ");                                        \
							}                                                               \
							printf(STRINGIZE(__FILE__) ", " STRINGIZE(__LINE__) ": diff --test --strip-trailing-cr " STRINGIZE(a) " " STRINGIZE(b) "\n");   \
						}

// Fonction à executer lors d'une segmentation fault.
// On imprime les résultats obtenus jusqu'à lors et on arrête immédiatement le programme.
void segfault_sigaction(int signal, siginfo_t *si, void *arg)
{
	std::cout << "[SEGFAULT]" << std::endl;
	std::cout << tests_reussis << "/" << tests_executes << std::endl;
	exit(tests_reussis - tests_executes);
}

int main()
{
	// Mise en place de la fonction à exécuter lors d'une segmentation fault.
	struct sigaction sa;
	memset(&sa, 0, sizeof(struct sigaction));
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = segfault_sigaction;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGSEGV, &sa, NULL);

	{
		//----------------------LIST---------------------
		auto l = List<int>();
		l.addlast(1);
		l.addlast(2);
		l.addlast(3);
		TEST(l.first->data == 1);
		TEST(l.first->next->data == 2);
		TEST(l.first->next->next->data == 3);
		TEST(l.length == 3);
		TEST(l[0] == 1);
		TEST(l[1] == 2);
		TEST(l[2] == 3);
		l.remove(2);
		TEST(l[0] == 1);
		TEST(l[1] == 3);
		TEST(l.length == 2);
		l.remove(1);
		TEST(l[0] == 3);
		l.remove(3);
		TEST(l.first == NULL);
		TEST(l.last == NULL);
	}

	std::cout << tests_reussis << "/" << tests_executes << std::endl;

	return tests_executes - tests_reussis;
}