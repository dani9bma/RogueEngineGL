/*
 * @module Utils
 * @project Skel Engine(https://github.com/dani9bma/SkelEngine)
 * @author Daniel Assunção
 * @Github https://github.com/dani9bma
 */

#pragma once

#include <stdio.h>
#include <Windows.h>

#define LOG_INFO(module, x, ...) {HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);\
			printf("[SKEL::" module"] "  x "\n", __VA_ARGS__);}

#define LOG_WARNING(module, x, ...) {HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);\
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); \
			printf("[SKEL::" module"] "  x "\n", __VA_ARGS__); \
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);}

#define LOG_ERROR(module, x, ...) {HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);\
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); \
			printf("[SKEL::" module"] "  x "\n", __VA_ARGS__); \
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);} 