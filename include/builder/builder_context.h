#ifndef BUILDER_CONTEXT
#define BUILDER_CONTEXT
#include <list>
#include <vector>
#include "blocks/expr.h"
#include "blocks/stmt.h"
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include "function_type_traits.h"


namespace builder {
class builder;
class var;
template <typename T>
class dyn_var;
template <typename... arg_types>
std::vector <block::expr::Ptr> extract_call_arguments_helper (const builder& first_arg, const arg_types&... rest_args);

template <typename T>
block::expr::Ptr create_foreign_expr (const T t);
template <typename T>
builder create_foreign_expr_builder (const T t);


template <typename...AllArgs>
struct extract_signature;

template <typename T, typename...OtherArgs>
struct extract_signature_from_lambda;

class tracking_tuple {
public:
        const unsigned char* ptr;
        uint32_t size;
        tracking_tuple (const unsigned char* _ptr, uint32_t _size): ptr(_ptr), size(_size) {}
	std::string snapshot(void) {
		std::string output_string;
		char temp[4];
		for (unsigned int i = 0; i < size; i++) {
			sprintf(temp, "%02x", ptr[i]);
			output_string += temp;	
		}
		return output_string;
	}
};


class tag_map {
public:
	std::unordered_map<std::string, block::stmt_block::Ptr> map;	
	
};
void lambda_wrapper(void);
void lambda_wrapper_impl(void);


void function_wrapper(void);
void function_wrapper_impl(void);

class builder_context {
public:

	typedef void (*ast_function_type)(void);

	
	std::list <block::block::Ptr> uncommitted_sequence;
	block::stmt::Ptr ast;
	block::stmt_block::Ptr current_block_stmt;	
	ast_function_type current_function;

	
	std::vector<bool> bool_vector;
	std::unordered_set<std::string> visited_offsets;

	tag_map _internal_tags;
	tag_map *memoized_tags;

	bool is_visited_tag (tracer::tag &new_tag);
	void erase_tag(tracer::tag &erase_tag);
		
	builder_context(tag_map *_map = nullptr) {
		if (_map == nullptr) {
			memoized_tags = &_internal_tags;
		} else {
			memoized_tags = _map;
		}
		current_block_stmt = nullptr;
		ast = nullptr;
	}

	void commit_uncommitted(void);	
	void remove_node_from_sequence(block::expr::Ptr);
	void add_node_to_sequence(block::expr::Ptr);
	
	void add_stmt_to_current_block(block::stmt::Ptr, bool check_for_conflicts = true);


	block::stmt::Ptr extract_ast(void);
	block::stmt::Ptr extract_ast_from_lambda(std::function<void (void)>);
	block::stmt::Ptr extract_ast_from_function(ast_function_type);
	block::stmt::Ptr extract_ast_from_function_impl(ast_function_type);
	block::stmt::Ptr extract_ast_from_function_internal(ast_function_type, std::vector<bool> bl = std::vector<bool>());


	block::func_decl::Ptr current_func_decl;
	template <typename F, typename...OtherArgs>
	block::stmt::Ptr extract_function_ast(F func_input, std::string func_name, OtherArgs&...other_args) {
		current_func_decl = std::make_shared<block::func_decl>();
		current_func_decl->func_name = func_name;
		// The extract_signature_from_lambda will update the return type 
		current_func_decl->body = extract_ast_from_lambda(extract_signature_from_lambda<F, OtherArgs&...>::from(this, func_input, func_name, other_args...));
		return current_func_decl;
	}

	
	std::string current_label;


	std::vector<tracking_tuple> static_var_tuples;
	
	std::vector<var*> assume_variables;
	
	template <typename T>
	T* assume_variable (std::string name) {
		T *new_asm_variable = new T(true);
		new_asm_variable->block_var->var_name = name;
		assume_variables.push_back(new_asm_variable);
		
		return new_asm_variable;	
	}	
	~builder_context();
private:
	std::function<void (void)> internal_stored_lambda;
	ast_function_type internal_stored_function;
	

	static builder_context *current_builder_context;
	friend builder;
	friend var;

	template <typename T>
	friend class dyn_var;
	template <typename T>
	friend class static_var;

	template <typename... arg_types>
	friend std::vector <block::expr::Ptr> extract_call_arguments_helper (const builder& first_arg, const arg_types&... rest_args);

	friend void annotate(std::string);
	friend tracer::tag get_offset_in_function(ast_function_type _function);
	friend void lambda_wrapper_impl(void);
	friend void function_wrapper_impl(void);

	template <typename T>
	friend block::expr::Ptr create_foreign_expr (const T t);
	template <typename T>
	friend builder create_foreign_expr_builder (const T t);
	
	friend void create_return_stmt(const builder a);
};
bool get_next_bool_from_context(builder_context *context, block::expr::Ptr);
tracer::tag get_offset_in_function(builder_context::ast_function_type _function);

}

#endif
