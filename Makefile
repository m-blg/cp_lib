
build_dir := ./target
src_dir := ./src
test_dir := ./tests

all:

.PHONY: run
run: 
	@#@if [ -z $(test) ]; then\
        #echo "null";\
	#else\
		#echo $(test);\
	#fi
ifdef test
	echo "test: $(test)"
	@make $(build_dir)/tests/$(test)
	$(build_dir)/tests/$(test)
endif

$(build_dir)/tests/%: $(test_dir)/%.cc
	mkdir -p $(build_dir)/tests
	@g++ -g $(test_dir)/$(notdir $@).cc -o $@



