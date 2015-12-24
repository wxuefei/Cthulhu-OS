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
 * task.c
 *  Created on: Dec 23, 2015
 *      Author: Peter Vanusanik
 *  Contents: task management
 */

#include "task.h"

array_t* cpus;

cpu_t* make_cpu(MADT_LOCAL_APIC* apic) {
	cpu_t* cpu = malloc(sizeof(cpu_t));
	if (cpu == NULL)
		error(ERROR_MINIMAL_MEMORY_FAILURE, 0, 0, &make_cpu);
	cpu->acip = apic->processor_id;
	cpu->started = false;
	cpu->processes = create_array();
	if (cpu->processes == NULL)
		error(ERROR_MINIMAL_MEMORY_FAILURE, 0, 0, &make_cpu);
	return cpu;
}

cpu_t* make_cpu_default() {
	cpu_t* cpu = malloc(sizeof(cpu_t));
	if (cpu == NULL)
		error(ERROR_MINIMAL_MEMORY_FAILURE, 0, 0, &make_cpu);
	cpu->acip = 0;
	cpu->started = false;
	cpu->processes = create_array();
	if (cpu->processes == NULL)
		error(ERROR_MINIMAL_MEMORY_FAILURE, 0, 0, &make_cpu);
	return cpu;
}

void initialize_cpus() {
	cpus = create_array();
	unsigned int cnt = 0;
	MADT_LOCAL_APIC* apicptr = NULL;

	while ((apicptr=find_madt(ACPI_MADT_TYPE_LOCAL_APIC, cnt))!= NULL) {
		array_push_data(cpus, make_cpu(apicptr));
		++cnt;
	}

	if (cnt == 0){
		// no acpi, use single cpu only
		array_push_data(cpus, make_cpu_default());
	}
}

void initialize_kernel_task() {

}
