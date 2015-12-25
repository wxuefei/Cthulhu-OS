/*
 * The MIT License (MIT)
 * Copyright (c) 2015 Peter Vanusanik <admin@en-circle.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy 
 * of this software and associated documentation files (the "Software"), to deal in 
 * the Software without restriction, including without limitation the rights to use, copy, 
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, subject to the 
 * following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies 
 * or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS 
 * OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * task.h
 *  Created on: Dec 23, 2015
 *      Author: Peter Vanusanik
 *  Contents: task management
 */

#pragma once

#include "../commons.h"
#include "../utils/random.h"
#include "../memory/paging.h"
#include "../utils/collections/array.h"
#include "../structures/acpi.h"

#include <stdlib.h>
#include <string.h>

typedef struct file_descriptor {
	uint32_t fd_pid;
	uint64_t owner_daemon;
} fd_t;

typedef enum mmap_area_type {
	allocation
} ma_type_t;

typedef struct mmap_area {
	uint64_t  vastart;
	uint64_t  vaend;
	ma_type_t mtype;

	struct mmap_area_t* next;
} mmap_area_t;

typedef struct thread thread_t;

typedef struct proc {
	uint64_t     proc_id;
	uint64_t     pml4;

	char**       environ;
	char**       argc;
	unsigned int argv;

	array_t* 	 fds;
	array_t* 	 threads;

	mmap_area_t* mem_maps;
} proc_t;

struct thread {
	uint32_t tId;
	proc_t*  parent_process;
	uint64_t last_rip;
	uint64_t last_rsp;

	uint64_t stack_top_address;
	uint64_t stack_bottom_address;
};

typedef struct cpu {
	void*	 stack;
	uint64_t processor_id;
	uint8_t  apic_id;
	bool     started;
	array_t* processes;
} cpu_t;

extern array_t* cpus;

void initialize_cpus();
void initialize_kernel_task();
