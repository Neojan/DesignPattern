#!/bin/bash


# notice:shell脚本对空格有严格的规定，赋值语句等号两边不能有空格，而字符串比较，等号两边必须有空格

project_name="DESIGN_PATTERN"
export version_major="1"
export version_minor="0"
export version_patch="0"

platform_list=("x86")
platform_defalut="x86"

version_code="V${version_major}.${version_minor}.${version_patch}"

function build_help()
{
    echo "${shell_relative_name} options:"
    echo "options:"
    echo -e " -p platform, --platform=platform    \c" # -e开启转义 \c表示不加换行符号
    echo "choose platform to compile, not we support <${platform_list[@]}>, default ${platform_defalut}"
    echo -e " -b branch, --branch=branch   \c"
    echo "choose comiple mode, <${build_mode_list[@]}, default ${build_mode_default}>"
    echo -e " --clean   \c"
    echo "clean compile"
    echo -e " --help   \c"
    echo -e "help info \n"
}

function mkdir_lib_path()
{
    [ -d ${install_path}/${platform}/libs ] || mkdir -p ${install_path}/${platform}/libs
    [ -d ${install_path}/${platform}/include ] || mkdir -p ${install_path}/${platform}/include
}

#校验传入的编译模式是否正确 release/debug
# Input param: 编译模式 
function check_build_mode()
{
    build_mode_input=$1
    for build_mode_tmp in ${build_mode_list[@]}  # 使用 @ 或 * 可以获取数组中的所有元素
    do
        if [ "${build_mode_input}" == "${build_mode_tmp}" ];
        then
            return 0
        fi
    done

    echo "error: not support build_mode: ${build_mode_input}"
    echo ""
    build_help
    echo ""
    echo "BUILD FAIL [${shell_name}]"
    exit 1
}

#校验传入的平台是否正确
# Input param: 平台 
function check_platform()
{
    platform_input=$1

    for platform_tmp in ${platform_list[@]} "all"
    do
        if [ "${platform_input}" = "${platform_tmp}" ];
        then
            return 0
        fi
    done

    echo "error: not support platform: ${platform_input}"
    echo ""
    build_help
    echo ""
    echo "BUILD FAIL [${shell_name}]"
    exit 1
}

# 编译指定平台
function build_by_platform()
{
    if [ ${#platform_pre} = 3 ] && [ ${platform_pre} = "all" ];
    then
        echo "Build all platform, List of build platform is ${platform_list[@]}"
        for platform in ${PLATFORM_LIST[@]}
        do
            echo ""
            echo "Start build ${platform}"
            export platform=${platform}
            build linux
        done
    else
        echo "List of build platform is ${platform_pre} "
        for platform in ${platform_pre}
        do
            echo ""
            echo "Start build ${platform}"
            export platform=${platform}
            build linux
        done
    fi
}

function build()
{
    for os in $@ ; do
        case ${os} in
            linux)
                if [ "${platform}" == "x86" ]; then
                    export cross_toolchain=
                    export extensions="GNU"
                else
                    echo "error platform: ${platform}"
                    build_help
                    echo ""
                    echo "build fail [${shell_name}]"
                fi;;
            *)
                echo "error os $1"
                echo ""
                echo "build fail [${shell_name}]"
                exit 1;;
        esac

        echo "#########################"
        echo "    build ${platform}    "
        echo "#########################"

        export cross_toolchain
        export platform
        build_base ${platform} ${cross_toolchain}
    done
}


#清除编译临时文件
function build_clean()
{
    rm -rf ${work_path}
    rm -rf ${install_path}
    echo "#########################################"
    echo "   clean finish  [${shell_name}] "
    echo "#########################################"
    echo ""
}

#执行编译 参数1平台，参数2工具链名称
function build_base()
{
    work_platform_path=${work_path_cur_script}/_build-${platform}  #工作目录
    echo ${work_path_cur_script}
    [ -d ${work_platform_path} ] || mkdir -p ${work_platform_path}

    cd ${work_platform_path}

    #生成版本信息
    echo ${extensions}
    if [ "${extensions}" == "GNU" ]; then
        cmake ${make_path}
    elif [ "${extensions}" == "ANDROID" ]; then
        cmake ${make_path} \
            -DCMAKE_TOOLCHAIN_FILE=${NDK_TOOLCHAIN_FILE} \
            -DANDROID_NDK=${ANDROID_NDK_HOME} \
            -DANDROID_ABI=${NDK_ABI} \
            -DANDROID_TOOLCHAIN=${CC} \
            -DANDROID_PLATFORM=${NDK_PLATFORM} \
            -DANDROID_STL=${NDK_STL} \
            -DANDROID_ALLOW_UNDEFINED_SYMBOLS=true
    fi
    
    make -j${make_jobs} VERBOSE=1  || exit 1 #VERBOSE=1 
    make install || exit 1

    mkdir_lib_path
}

## entry


# dirname $0，获取当前Shell程序的路径
shell_relative_name=$0 # $0：当前Shell程序的文件名
shell_folder=$(cd `dirname "$0"`; pwd)  # script path，反引号执行命令输出值符给变量，$() 与 反引号 `` 其实效果是一样的
shell_name=${shell_folder}/`basename "$0"` # 当前脚本绝对路径名称

export root_path=$(cd `dirname "$0"`/..; pwd)
make_path=${root_path}/src/ # source code path

echo -e "Build start [${shell_name}] \n"

# 解析参数
# args_init=$@
#-o或--options选项后面接可接受的短选项，如ab:c::，表示可接受的短选项为-a -b -c，其中-a选项不接参数，-b选项后必须接参数，-c选项的参数为可选的
#-l或--long选项后面接可接受的长选项，用逗号分开，冒号的意义同短选项。
#-n选项后接选项解析错误时提示的脚本名字
ARGS=`getopt -o p:b:j:: -a -l "platform:,branch:,help,clean,jobs::" -n "${shell_name}" -- "$@"`
echo ARGS=[$ARGS]
#将规范化后的命令行参数分配至位置参数（$1,$2,...)
eval set -- "${ARGS}"

# 位置参数可以用shift命令左移。比如shift 3表示原来的$4现在变成$1，原来的$5现在变成$2等等，原来的$1、$2、$3丢弃，$0不移动。不带参数的shift命令相当于shift 1。
while true;
do
    case "$1" in
        -p | --platform) 
            platform_pre=$2
            shift 2
            ;;
        -b | --branch)
            build_mode=$2
            echo "${build_mode}"
            shift 2
            ;;
        --clean)
            build_clean
            exit 0
            ;;
        --help)
            build_help
            exit 0
            ;;
        --)
            shift 1
            break
            ;;
        *)
            build_help
            exit 1
            ;;
    esac
done

work_path=${root_path}/.work
build_path=${root_path}/build
[ -z "${install_path}"] && export install_path=${root_path}/install
[ -z "${rely_path}"] && export rely_path=${root_path}/rely
export cmake_path=${root_path}/cmake
work_path_cur_script=${work_path}$(echo ${shell_folder} | sed "s|${root_path}||") # build 目录
# -n:检测字符串长度是否不为 0，不为 0 返回 true
# -z:检测字符串长度是否为0，为0返回 true


build_mode_list=("release" "debug")
build_mode_default="release"
make_jobs="12"
build_flag="yes"
prepare_flag="yes"


#检查编译模式 有效性
[ -z "${build_mode}" ] && build_mode=${build_mode_default}
echo -e "build_mode: ${build_mode} \n"
check_build_mode ${build_mode}
export build_mode


# 检验编译平台 有效性
[ -z "${plaform_pre}" ] && plaform_pre=${plaform_default}
# plaform_pre=${plaform_pre//","/" "}  支持多平台时再启用
echo -e "platform:  ${plaform_pre} \n"
for platform_index in $plaform_pre
do
    check_platform ${platform_index}
done

#执行编译
build_by_platform


echo -e "BUILD SUCCESS [${shell_name}] \n"
exit 0
