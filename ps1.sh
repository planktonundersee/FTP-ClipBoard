#!/bin/bash
#   Description: 为方便运维,开发该脚本“美化”Linux终端
#   Usage:
#       0. 修改IpCfg的值。在$IpCfg中配置的登录的用户,该脚本才会生效
#       1. cp ps1.sh ~/.ps1.sh
#       2. echo -e '# 设置自定义shell终端输出\n source ~/.ps1.sh' >> ~/.bashrc
#       3. 生效。重新登录一次或执行 source ~/.bashrc
#

# shellcheck disable=SC2219
# shellcheck disable=SC2034
# shellcheck disable=SC2219
# shellcheck disable=SC1001

temp="$(tty)"
#   Chop off the first five chars of tty (ie /dev/):
cur_tty="${temp:5}"
unset temp

function parse_git_branch() {
    # shellcheck disable=SC2155
    local branchName=$(git branch 2> /dev/null | sed -e '/^[^*]/d' -e 's/* \(.*\)/(\1)/')
    if [[ $branchName ]]; then
        echo "$branchName"
    fi
}
branch=$(parse_git_branch)

function prompt_command {
UserName=$(whoami)
ip=$(ifconfig | grep "inet" | awk '{print $2}' |awk 'NR==1')
dirPath=$(pwd)
newPWD="$UserName@$ip:$dirPath"
TheTime=$(date +%Y-%m-%d\ %a\ %H:%M:%S)
TERMWIDTH=${COLUMNS}

#TotalSize=$(stty size|awk '{print $2}')
local temp="|-(${newPWD}:${cur_tty}:${branch})---(${TheTime})-|"
let FillSize=$TERMWIDTH-${#temp}

if [ "$FillSize" -gt "0" ]
then
    Fill="--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"
    Fill="${Fill:0:${FillSize}}"
    UserName=$(whoami)
    ip=$(ifconfig | grep "inet" | awk '{print $2}' |awk 'NR==1')
    dirPath=$(pwd)
    newPWD="$UserName@$ip:$dirPath"
    TheTime=$(date +%Y-%m-%d\ %a\ %H:%M:%S)
    local temp="|-(${newPWD}:${cur_tty}:${branch})---(${TheTime})-|"
    let FillSize=${TERMWIDTH}-${#temp}
fi

if [ "$FillSize" -lt "0" ]
then
    Fill="-------------------"
    UserName=$(whoami)
    ip=$(ifconfig | grep "inet" | awk '{print $2}' |awk 'NR==1')
    dirPath=$(pwd)
    shortDir=$dirPath
    shortPWD=${shortDir##*/}
    newPWD="$UserName@$ip:$shortPWD"
    TheTime=$(date +\%H:%M:%S)

    local temp="(${newPWD}:${cur_tty}:${branch})-------(${TheTime})"
    let FillSize=${TERMWIDTH}-${#temp}

    if [ "$FillSize" -gt "0" ]
    then
        Fill="--------------------------------------------------------------"
        Fill="${Fill:0:${FillSize}}"
        UserName=$(whoami)
        ip=$(ifconfig | grep "inet" | awk '{print $2}' |awk 'NR==1')
        dirPath=$(pwd)
        shortDir=$dirPath
        shortPWD=${shortDir##*/}
        newPWD="$UserName@$ip:$shortPWD"
        TheTime=$(date +\%H:%M:%S)

        local temp="(${newPWD}:${cur_tty}:${branch})---(${TheTime})"
        let FillSize=${TERMWIDTH}-${#temp}
    fi

    if [ "$FillSize" -lt "0" ]
    then
        Fill=""
        UserName=$(whoami)
        ip=$(ifconfig | grep "inet" | awk '{print $2}' |awk 'NR==1')
        dirPath=$(pwd)
        shortDir=$dirPath
        shortPWD=${shortDir##*/}
        newPWD="$UserName@$ip:$shortPWD"
        TheTime=$(date +\%H:%M:%S)

        local temp="(${newPWD}:${cur_tty}:${branch})---(${TheTime})"
        let FillSize=${TERMWIDTH}-${#temp}
    fi

fi
}

PROMPT_COMMAND=prompt_command

function refreshSSH() {
local WHITE="\[\033[1;37m\]"
local NO_COLOUR="\[\033[0m\]"
local WHITE="\[\033[1;37m\]"
local LIGHT_BLUE_1="\[\033[1;36m\]"
local PURPLE_RED="\[\033[1;35m\]"
local LIGHT_BLUE="\[\033[1;34m\]"
local YELLOW="\[\033[1;33m\]"
local LIGHT_GREEN="\[\033[0;32m\]"
local RED="\[\033[1;31m\]"
local BLACK="\[\033[1;30m\]"

case $TERM in
    xterm*|rxvt*)
        TITLEBAR='\[\033]0;\u@\h:\w\007\]'
        ;;
    *)
        TITLEBAR=""
        ;;
esac
hostname=$(hostname)
# shellcheck disable=SC2154
PS1="$TITLEBAR$WHITE|$RED-$LIGHT_BLUE(\
$LIGHT_BLUE\${newPWD}$LIGHT_BLUE $LIGHT_BLUE_1\${cur_tty}$YELLOW:$LIGHT_GREEN\$(parse_git_branch)\
$LIGHT_BLUE)$RED-${RED}-\${Fill}\
${RED}-$LIGHT_BLUE($PURPLE_RED\${TheTime}$LIGHT_BLUE)$RED-$WHITE|\
\n\
$RED\${hostname}$LIGHT_BLUE:$WHITE\$\
$NO_COLOUR "

}

refreshSSH

