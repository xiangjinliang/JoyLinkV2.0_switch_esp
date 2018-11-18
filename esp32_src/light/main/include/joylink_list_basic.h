/*Copyright (c) 2015-2050, JD Smart All rights reserved.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License. */

#ifndef _YC_LLIST_H
#define _YC_LLIST_H

#include "joylink_list.h"

#ifdef __cplusplus
extern "C"
{
#endif

struct yc_list_head {
	struct yc_list_head *next;
	struct yc_list_head *prev;
};

/**
 * initiate the list
 */
#define INIT_LIST_HEAD(head) do {			\
		(head)->next = (head)->prev = head;	\
	} while (0)


/**
 * add new list_head into one list at the beginning
 * (generally speaking, the first element in one list doesn't contain an structure, i.e. simple list_head object)
 */
static inline void yc_list_add (struct yc_list_head *_new, struct yc_list_head *head)
{
	_new->prev = head;
	_new->next = head->next;

	_new->prev->next = _new;
	_new->next->prev = _new;
}

/**
 * add _new list_head into one list at the ending
 * (generally speaking, the first element in one list doesn't contain an structure, i.e. simple list_head object)
 */
static inline void yc_list_add_tail (struct yc_list_head *_new, struct yc_list_head *head)
{
	_new->next = head;
	_new->prev = head->prev;

	_new->prev->next = _new;
	_new->next->prev = _new;
}

/**
 * delete an yc_list_head from the list containing it
 */
static inline void yc_list_del (struct yc_list_head *old)
{
	old->prev->next = old->next;
	old->next->prev = old->prev;

    old->next = (struct yc_list_head *)0xaaaaaaaa;
    old->prev = (struct yc_list_head *)0xbbbbbbbb;

}

/**
 * delete an list_head from the list containing it
 * and initite itself
 */
static inline void yc_list_del_init (struct yc_list_head *old)
{
	old->prev->next = old->next;
	old->next->prev = old->prev;

	old->next = old;
	old->prev = old;
}

/**
 * check if the list is empty
 * (generally speaking, the first element in one list doesn't contain an structure, i.e. simple yc_list_head object
 */
static inline int yc_list_empty (struct yc_list_head *head)
{
	return (head->next == head);
}

static inline int yc_list_size(struct yc_list_head *head){
	struct yc_list_head* find;
	int num;

	num = 0;
	find = head->next;
	while(find != head){
		num ++;
		find = find->next;
	}

	return num;
}

#define joylink_list_size yc_list_size

/**
 * from the structure member to the the structure
 * eg:
 * struct exa_struct{
 * 		int a;
 * 		list_head here_pos;
 * 		...;
 * }
 *
 * list_head *my_head = ...; //which is contained in the exa_sturct structure
 *
 * //you can get the exa_structure pointer by
 * exa_struct *p = list_entry(my_head, struct exa_struct, here_pos);
 *
 */
#define list_entry(ptr, type, member)					\
	((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

/**
 * traverse the whole list. Notice, the first one list_head not containing 
 * the structure, which only stands for an list_head object
 *
 * you can use like this:
 *
 * list_head* head;
 * ...
 * ...
 *
 * list_head* trav_head;
 * list_for_each(trav_head, head){
 * 	....
 * 	....
 * 	....
 * }
 */
#define list_for_each(pos, head)				     \
	for (pos = (head)->next; pos != (head); pos = pos->next)
#if defined (__ANDROID__)
/**
 * pos: structure pointer
 * head: list header
 * member: name of list_head in the structure
 */
#define list_for_each_entry(pos, head, member)				\
	for (pos = list_entry((head)->next, __typeof__(*pos), member);	\
	     &pos->member != (head); 					\
	     pos = list_entry(pos->member.next, __typeof__(*pos), member))

/**
 * pos: structure pointer, used in the loop body
 * n: structure pointer, not used in the loop body
 * head: list header
 * member: name of list_head in the structure
 */
 
#define list_for_each_entry_safe(pos, n, head, member)			\
	for (pos = list_entry((head)->next, __typeof__(*pos), member),	\
		n = list_entry(pos->member.next, __typeof__(*pos), member);	\
	     &pos->member != (head); 					\
	     pos = n, n = list_entry(n->member.next, __typeof__(*n), member))
#else

/**
 * pos: structure pointer
 * head: list header
 * member: name of list_head in the structure
 */
#define list_for_each_entry(pos, head, member)				\
	for (pos = list_entry((head)->next, typeof(*pos), member);	\
	     &pos->member != (head); 					\
	     pos = list_entry(pos->member.next,typeof(*pos), member))

/**
 * pos: structure pointer, used in the loop body
 * n: structure pointer, not used in the loop body
 * head: list header
 * member: name of list_head in the structure
 */
#if defined(__MICOKIT_3166__) || defined(__REALTEK_8711__)
#define list_for_each_entry_safe(pos, n, head, member)			\
	for (pos = list_entry((head)->next, jl_id_node_t, member),	\
		n = list_entry(pos->member.next, jl_id_node_t, member);	\
	     &pos->member != (head); 					\
	     pos = n, n = list_entry(n->member.next, jl_id_node_t, member))

#else
#define list_for_each_entry_safe(pos, n, head, member)			\
	for (pos = list_entry((head)->next, typeof(*pos), member),	\
		n = list_entry(pos->member.next, typeof(*pos), member);	\
	     &pos->member != (head); 					\
	     pos = n, n = list_entry(n->member.next, typeof(*n), member))
#endif
#endif

typedef struct yc_list_head jl_list_head_t;

#ifdef __cplusplus
}
#endif
#endif /* _LLIST_H */
