# 基础版 Makefile (Verilator + 波形)

# 定义 Verilator 相关变量
VERILATOR = verilator
VERILATOR_FLAGS = -Wall -Wno-fatal --cc --trace --exe --build # 常用选项

# 定义源文件和顶层模块
TOP_MODULE = top  # 你的顶层模块名称
VSRCS = $(wildcard vsrc/*.v)  # 自动查找 vsrc 目录下的所有 .v 文件
CSRCS = $(wildcard csrc/*.cpp) # 自动查找 csrc 目录下的所有 .cpp 文件

# 定义输出目录和可执行文件
OBJ_DIR = obj_dir
EXE = $(TOP_MODULE)

# 默认目标
all: $(OBJ_DIR)/$(EXE)
	@echo "Build successful!"

# 编译和仿真
$(OBJ_DIR)/$(EXE): $(VSRCS) $(CSRCS)
	$(VERILATOR) $(VERILATOR_FLAGS) $(VSRCS) $(CSRCS) --top-module $(TOP_MODULE) -o $(EXE)
	@mkdir -p $(OBJ_DIR)
	@if [ -f $(EXE) ]; then mv $(EXE) $(OBJ_DIR)/; fi

# 运行仿真
sim: $(OBJ_DIR)/$(EXE)
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	$(OBJ_DIR)/$(EXE)

# 清理
clean:
	rm -rf $(OBJ_DIR)
	rm -f *.fst

# 包含上级 Makefile (如果需要)
include ../Makefile
