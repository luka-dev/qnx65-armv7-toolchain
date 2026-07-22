#!/usr/bin/env python

"""applypatch.py

Apply a patch to the system or remove an already installed patch.
See usage for more information
"""

# Copyright 2009, QNX Software Systems. All Rights Reserved.
#
# This source code may contain confidential information of QNX Software 
# Systems (QSS) and its licensors.  Any use, reproduction, modification, 
# disclosure, distribution or transfer of this software, or any software 
# that includes or is based upon any of this code, is prohibited unless 
# expressly authorized by QSS by written agreement.  For more information 
# (including whether this source code file has been published) please
# email licensing@qnx.com.
#
# $URL: http://svn/product/branches/6.5.0/trunk/utils/a/applypatch/applypatch.py $ $Rev: 264792 $



import tarfile
import sys
import os
import getopt
from stat import *
from time import time,localtime,strftime
import platform
from signal import *

# Global settings: modified by command line options
verbose = False         # -v
destDir = ""            # -d
makeBackup = True       # -b
force = False           # -F
contentsOnly = False    # -c 
installAllHosts = False # -H

# Copy buffer size (256K)
bufSize = 256 * 1024
    
# Platform specific host paths. Setting here for visibility.
hostPaths = {
    "Windows"   : "host/win32/x86",
    "Microsoft" : "host/win32/x86", # Python 2.5.1 on Windows Vista reports Microsoft instead of Windows. 
    "QNX"       : "host/qnx6/x86",
    "Linux"     : "host/linux/x86"
}

def usage():
    print """
usage: applypatch.py [-b] [-c] [-d <path>] [-F] [-h or -?] [-H] [-v] patch_file
       or
       applypatch.py -U <num>
where:
       -b
       Do NOT provide a backup. This means you will not be able to roll 
       back this patch or any patches applied after this. This is not 
       recommended for general use.
       
       -c 
       Extract patch contents only. No metadata will be recorded nor 
       will any backup file be generated. This is useful when pulling out 
       individual files for testing but is not recommended for general use.  
       
       -d <path>
       Specify destination path. This path will be the root directory used
       for extracting the patch contents as well as for storing the patch 
       metadata. The default will be the currently active QNX SDP Installation.
        
      -F
      Turn off prompting by forcing a 'yes' answer to all queries.
      Normally newer files will not be overwritten by older files from the 
      patch. This option disables that check. This means locally updated files
      may be SILENTLY REPLACED by an older version from the patch. 
      
      -h -?
      This help.
      
      -H
      Install all host files. Normally only the files suitable for the running
      platform are installed. In the case of a server or if the patch is to 
      be applied by hand later on other platforms this option will install
      all host specific files. 
       
      -l
      List patches ordered by newest to oldest (based on installation time)
      
      -v 
      Verbose. Display some information on progress and activities.
      
      -U <num>
      Uninstall patch number <num>. Due to the nature of the patching process
      any patch which was installed after patch <num> will be uninstalled as
      well. In effect you will roll back to the state the system was in just
      before patch <num> _and all subsequent patches_ were applied.
"""
       
           
def main():
    global destDir, verbose, force, makeBackup, contentsOnly, installAllHosts
    dolist = False
    uninst = 0
    
    
    # Check for environment variables required before anything else
    if os.environ.has_key('QNX_TARGET') == False or os.environ.has_key('QNX_CONFIGURATION') == False:
        print "Error: Your environment is not set."
        sys.exit(1)

    # Set default destination directory
    destDir = getInstallationBase()
        
    try:
        opts, args = getopt.getopt(sys.argv[1:], "?hHbcd:FlnU:v")
    except getopt.GetoptError, err:
        # print help information and exit:
        print str(err)
        usage()
        sys.exit(2)
    for o, a in opts:
        if o == '-b':
            makeBackup = False
        elif o == '-c':
            contentsOnly = True
        elif o == '-d':
            destDir = a
        elif o == '-F':
            force = True
        elif o == '-H':
            installAllHosts = True
        elif o == '-l':
            dolist = True
        elif o == '-U':
            try:
                uninst = int(a)
            except ValueError:
                print "\nError: Invalid value for patch number. The valid values are"
                print "from the first column of the patch list.\n"
                print "Patch list:"
                listPatches()
                print
                sys.exit(1)
        elif o == '-v':
            verbose = True
        elif o == '-?' or o == '-h':
            usage()
            sys.exit(0)
        else:
            usage()
            sys.exit(2)
    
    # If there is a bad installation still in place this blocks any further
    # operation. 
    fp = findFailedPatches()
    if len(fp) > 0:
        print "\nError: One or more failed installations was detected. This must be resolved"
        print "before any further patch operations can be applied.\n"
        if confirmation("Would you like to remove the bad installations now? (y/n) ") == False:
            print "Exiting at user request."
            sys.exit(1)
        else:
            for p in fp:
                (b,s,n) = os.path.basename(p).partition('-')
                print "\nRemoving patch #%s" % n
                uninstallPatch(n, recovery=True, meta=p)
        
    # Get the current platform. If this is not one we know about then always
    # install all of the host files.
    if not platform.system() in hostPaths.keys():
        installAllHosts = True
        if verbose:
            print "Warning: Unknown platform ("+platform.system()+"."
            print "Installing all host files."
         
    # Check for valid operations
    if dolist and uninst > 0:
        print >>sys.stderr,"Error: Only one of -U and -l can be used"
    elif len(args) > 0 and dolist:
        print >>sys.stderr,"Error: Patch file specified with -l"
    elif len(args) > 0 and uninst > 0:
        print >>sys.stderr,"Error: Patch file specified with -U"  
    elif dolist:
        if makeBackup == False or contentsOnly == True or force == True:
            print >>sys.stderr,"Error: -l is not compatible with any other option"
        elif listPatches():
             sys.exit(0)
    elif uninst > 0:
        if makeBackup == False or contentsOnly == True:
            print >>sys.stderr,"Error: -U is not compatible with any other option"
        elif uninstallPatch(uninst):
            sys.exit(0)
    else:
        # Install a patch
        if len(args) == 0:
            print >>sys.stderr,"Error: Require a patch file name.\n"
            usage()
        elif os.path.exists(args[0]) == False:
            print >>sys.stderr,"Error: File not found: %s" % args[0]
        elif isValidPatch(args[0]) == False:
            print >>sys.stderr,"""
Error: This file is not a valid patch. You should consult any release notes 
which accompanied this file to determine if an alternate installation method 
should be used."""
        else:            
            if installPatch(args[0]):
                sys.exit(0)
    
    # Only positive results above resulted in a sys.exit. If we arrived here
    # there was a problem. This avoids lots of "if ... exit 0 else exit 1" statements
    sys.exit(1)


def isValidPatch(patchFile):
    """Helper utility to verify a given file is a valid patch"""
    
    if tarfile.is_tarfile(patchFile) == False:
        print >>sys.stderr,'Error: File is not a valid tar file'
        return False
    
    info = os.path.basename(patchFile).split('-',4)

    try:
        patchBase = info[1]
        patchNum = int(info[2])
    except:
        print >>sys.stderr,'Error: File name does not match standard patch conventions'
        return False
    
    try:
        fil = tarfile.open(patchFile,'r')
    except Exception,e:
        print >>sys.stderr, 'Unable to open file:'+e
        return False
    
    # The internal structure of the patch must match the base and number
    manifestfound = False
    pathfound = False
    rootdir = 'patches/%s-%04d' % (patchBase,patchNum)
    for item in fil:
        if item.name == rootdir+'/manifest':
            manifestfound = True
        if item.name.startswith(rootdir+'/target/') or item.name.startswith(rootdir+'/host/'):
            pathfound = True
    
    if manifestfound == False or pathfound == False:
        print >>sys.stderr, 'Error: Internal structure does not conform to a standard patch'
        return False

    return True
    
        
    
def confirmation(prompt):
    """Helper utility to standardise confirmation input"""
    
    retval = None
    try:
        while retval == None:
            ans = raw_input(prompt)
            if ans.lower() == 'yes' or ans.lower().startswith('y'):
                retval = True
            elif ans.lower() == 'no' or ans.lower().startswith('n'):
                retval = False
            else:
                print "Please answer 'yes' or 'no'"
    except KeyboardInterrupt:
        retval = False
        print 
    return retval

    
    
def getInstallationBase():
    """Return the base directory of the installation.
    
    If the environment is not set return the current directory. The environment
    should have already been verified by this point.
    """
    
    try:
        target = os.environ['QNX_TARGET']
    except KeyError:
       return "."
    
    return target.replace('/target/qnx6','')



def writeQConfig(num,base,desc,meta,dest):
    """Write out the data file so 'qconfig' reports this patch"""
    
    configDir = os.environ['QNX_CONFIGURATION']
    cfgFileName = configDir + "/qconfig/patch" + num + ".xml"
    cfgFile = open(cfgFileName,"w")
    
    print >>cfgFile,"""<?xml version="1.0" ?>
    <qnxPackageInstall>
        <package>
            <name>Patch #%d: %s</name>
            <version>%d</version>
            <base>%s</base>
            <installLocation>%s</installLocation>
            <metaDataDir>%s</metaDataDir>
        </package>
    </qnxPackageInstall>""" % (int(num),desc,int(num),base,dest,meta)

    if verbose:
        print "Writing qconfig file: %s" % cfgFileName 
    return(cfgFileName)



def extractFile(tarinfo,tfile,rootdir,basedir):
    """Extract a file from the tar into it's directory
    
    Files are stored in the patch tar as:
        patch/<base>-<num>/<fn>
    so if we want to move the file somewhere else (i.e. extract to /tmp instead
    of the default) we first need to strip off the root. The tarfile API doesn't
    allow for file renaming so we need to extract the file contents to the new
    location then apply the appropriate file information (i.e. owner, modification
    time, etc.). 
    
    Any OS or path errors here are handled in the calling function
    """
    
    # Output file name. Generated by splicing the destination with the 
    # portion of the tar member's path following patch/<base>-<num>
    outputname = os.path.join(basedir,tarinfo.name.replace(rootdir,''))
    
    if os.path.exists(os.path.dirname(outputname)) == False:
        os.makedirs(os.path.dirname(outputname))
    
    # If the destination file is going to be overwritten then perform some additional actions ...
    if os.path.exists(outputname) == True:
        # ... unless the user has instructed otherwise
        if force == False:
            # Compare modification times. Don't replace if the on-disk file is 
            # newer than the one in the patch
            fileTime = os.stat(outputname)[ST_MTIME]
            if fileTime > tarinfo.mtime:
                if confirmation("File is newer on disk than in patch:%s\nWould you like to replace? (y/n)" % tarinfo.name) == False:
                    raise OSError, "Aborting at user request (File %s is newer on disk)" % tarinfo.name

    if tarinfo.issym():
        if not platform.system() in ["Windows","Microsoft"]:
            # Symbolic links should be removed first to avoid confusion and errors
            if os.path.exists(outputname):
                os.unlink(outputname)
            os.symlink(tarinfo.linkname,outputname)
            if verbose:
                print "Link: %s -> %s" % (outputname,tarinfo.linkname)
        else:
            # Under windows we need to copy file contents to simulate a symlink so replace
            # the source with the link source. By doing this the resulting file is a 
            # true copy.
            if tarinfo.issym() and platform.system() in ["Windows","Microsoft"]:
                # See if the link source is present in the tar file. Take the directory of the 
                # destination and splice on the full link name (it is always assumed to be relative)
                linksource = os.path.join(os.path.dirname(tarinfo.name),tarinfo.linkname)
                # Normpath is used to sort out ../ but also replaces any / with \. Tar requires / so fix it up as well.
                linksource = os.path.normpath(linksource).replace('\\','/')
    
                # There is the possibility of a link pointing to another link. In this case we need to 
                # get the contents of the real file so we need to 'follow' the links. Put a limit
                # to avoid infinite loops
                for count in range(1,10):
                    try:
                        linktarinfo = tfile.getmember(linksource)
                    except KeyError:
                        # The link source was not found. The assumption, then, is that this is a broken link
                        # so ignore it. We don't want to modify files outside of the patch which would be the case
                        # where a link changes what it points to.
                        print >>sys.stderr,"Error: Could not find link: source=%s dest=%s" % (tarinfo.linkname,tarinfo.name)
                        return False
                    if linktarinfo.issym():
                        linksource = os.path.join(os.path.dirname(linktarinfo.name),linktarinfo.linkname)
                        linksource = os.path.normpath(linksource).replace('\\','/')
                    else:
                        break
                else:
                    print >>sys.stderr,"Error: Could not find link: source=%s dest=%s" % (tarinfo.linkname,tarinfo.name)
                    return False
                extractFileContents(linktarinfo,tfile,os.path.dirname(outputname),os.path.basename(outputname))
                os.utime(outputname,(linktarinfo.mtime,linktarinfo.mtime))
                os.chmod(outputname,linktarinfo.mode)
                if verbose:
                    print "Link (copy): %s -> %s" % (outputname,tarinfo.linkname)
    else:   
        # Get the member file contents from the tar
        try:
            infile = tfile.extractfile(tarinfo)
        except KeyError,e:
            print >>sys.stderr,"Error: Extraction failed for %s: %s" % (outputname,str(e))
            return False
        
        if infile == None:
            print >>sys.stderr,"Error: Unknown type: %s" % tarinfo.name
            return False
        
        outfile = open(outputname,"wb")
        buf = infile.read(bufSize)
        # Copy data from tar file to physical file
        while buf != '':
            outfile.write(buf)
            buf = infile.read(bufSize)
        outfile.close()
        infile.close()
        
        # Restore file information.
        # Due to security some Linux distributions will remove any suid or
        # setgid bits if the file is touched. Thus we always set the mode last.
        if not platform.system() in ["Windows","Microsoft"]:
            os.chown(outputname,tarinfo.uid,tarinfo.gid)
        os.utime(outputname,(tarinfo.mtime,tarinfo.mtime))
        os.chmod(outputname,tarinfo.mode)
        if verbose:
            print "Extracted: %s" % (outputname)
    return True



def extractFileContents(tarinfo,tfile,basedir,filename=None):
    """Extract a file from the tar into an arbitrary location
    
    Instead of simply extracting a member to the path provided in the tar file
    extract the file to a totally different path. This is accomplished by 
    generating a new output file name then using the extractfile() function to
    retrieve the file data from the tar file. 
    
    If filename is set then also rename the file
    """
    
    if filename is None:
        filename = os.path.basename(tarinfo.name)
    outputname = os.path.join(basedir,filename)
    try:
        infile = tfile.extractfile(tarinfo)
    except KeyError,e:
        print >>sys.stderr,"Error: Extraction failed for %s: %s" % (outputname,str(e))
        return False
    
    if infile == None:
        print >>sys.stderr,"Error: Unknown type: %s" % tarinfo.name
        return False
    
    outfile = open(outputname,"wb")
    buf = infile.read(bufSize)
    while buf != '':
        outfile.write(buf)
        buf = infile.read(bufSize)
    outfile.close()
    infile.close()
    if verbose:
        print "Extracted: %s" % outputname
    return True


def findFailedPatches():
    """Detect if any patch installations have failed
    
    If a patch installation failed (i.e. power outage, etc.) then this must
    be removed prior to the installation of any other patch
    """
    
    patchesDir = "%s/install/patches/" % getInstallationBase()
    
    returnList = list()
    
    if os.path.exists(patchesDir):
        for patch in os.listdir(patchesDir):
            if patch == 'installation.dat':
                continue
            patchPath = os.path.join(patchesDir,patch)
            if os.path.isdir(patchPath) == True:
                if os.path.exists(os.path.join(patchPath,'inst.lck')) == True:
                    returnList.append(patchPath)
    return returnList




def saveCheckPoint(meta,state):
    """Record state of installation so recovery can be attempted on failure"""
    
    try:
        f = open(os.path.join(meta,"inst.lck"),'w')
        f.write(state)
        f.close()
    except Exception,e:
        print >>sys.stderr,"Error: Could not save state:",e
        return False
    return True


def getCheckPoint(meta):
    """Return saved state of installation so recovery can be attempted"""
    try:
        f = open(os.path.join(meta,"inst.lck"),'r')
        state = f.readline()
        f.close()
    except:
        return None
    return state


def delCheckPoint(meta):
    """Remove checkpoint file (indicating a successful installation"""
    try:
        os.unlink(os.path.join(meta,"inst.lck"))
    except Exception,e:
        print >>sys.stderr,"Error: Could not remove state:",e
        return False
    return True


def installPatch(filename):
    """Install a patch
    
    The patch installation procedure is:
      - Determine the meta data from the patch file name
      - Extract the files into the destination location
      - Record metadata
      - Generate a configuration file so the user can list what is installed
    """
    
    
    # Based on the patch file name figure out the baseline version, patch number
    # and brief description. This information will later be used when generating
    # the user-visible metadata.
    info = filename.split('-',4)
    patchBase = info[1]
    patchNum = info[2]
    (patchDesc,e1,e2) = '-'.join(info[3:]).partition('.t') # Assume the file name ends in one of .tar, .tar.gz, .tgz

    patchMetaDir = "%s/install/patches/%s-%s" % (getInstallationBase(),patchBase,patchNum)
    backupFileName = os.path.join(patchMetaDir,"uninstall.dat")

    # Check for a previous failed installation
    if getCheckPoint(patchMetaDir) != None:
        print >>sys.stderr,"Error: A previous installation of this patch had failed."
        print >>sys.stderr,"Restoring previous system state before attempting installation"
        uninstallPatch(patchNum,recovery=True,meta=patchMetaDir)
        
    if force == False and confirmation("\nPlease confirm you would like to install patch %s (%s): (y/n) " % (patchNum,patchDesc)) == False:
        print "\nPatch installation aborted at user request"
        return False
    
    try:
        if os.path.exists(destDir) == False:
            try:
                os.makedirs(destDir)
            except OSError,e:
                print "Error: Unable to create destination directory (%s)." % e
                return False
        
        # Metadata generation
        if contentsOnly == False:    
            if os.path.exists(patchMetaDir) == False:
                try:
                    os.makedirs(patchMetaDir)
                except OSError,e:
                    # We can't make the directory. Fatal error so halt.
                    print >>sys.stderr,"Error: Unable to create metadata (%s)." % e
                    return False
            else:
                # The meta directory exists. Is this patch already present?
                if os.path.exists(os.path.join(patchMetaDir,'filelist.dat')) == True:
                    print >>sys.stderr,"Error: Patch %s is already installed" % patchNum
                    return False
    
        saveCheckPoint(patchMetaDir,"INIT")                
    
    
        if verbose == True:
            print "Opening patch %s for %s. Desc is \"%s\"" % (patchNum,patchBase,patchDesc)
        
        # The internal structure of the patch tar file is rooted at this 
        # directory. In order to create the proper tree we need to strip 
        # out the root
        patchRoot='patches/%s-%s/' % (patchBase,patchNum)
        
        patchfile = tarfile.open(filename,"r")
        
        # Generate list of known meta files for comparison later
        metaFiles = [patchRoot+x for x in ('caution.gif','pointing.gif','shiplist','manifest','version')]
        
        # In order to facilitate the failure recovery process the backup is made
        # prior to any files being overwritten
            
        if makeBackup == True and contentsOnly == False:
            if verbose == True:
                print "Creating backup file:"
            backupFile = tarfile.open(backupFileName,"w:gz")
            for item in patchfile:
                if item.name in metaFiles or item.name.startswith(patchRoot+'inst_') or item.name.startswith(patchRoot+'rel_'):
                    # Skip metadata
                    continue
                if item.isdir():
                    continue
                fn = os.path.join(destDir,item.name.replace(patchRoot,''))
                if os.path.exists(fn):
                    backupFile.add(fn)
                    if verbose == True:
                        print "  Added:",fn
            backupFile.close()
            if verbose == True:
                print "done"
            saveCheckPoint(patchMetaDir,"BACKUP")
            
    
        # This list records any files written. It will be used to 
        # clean up in the event of a rollback
        fileListName = os.path.join(patchMetaDir,"filelist.dat")
        fileList = open(fileListName,"w")
        
        # Process tar file member by menber     
        try:   
            for member in patchfile:
                # Skip directories
                if member.isdir():
                    continue
                
                # Is this metadata? Check against generated list of known files 
                # as well as installation or release notes
                if member.name in metaFiles or member.name.startswith(patchRoot+'inst_') or member.name.startswith(patchRoot+'rel_'):
                    if contentsOnly == False:
                        extractFileContents(member, patchfile, patchMetaDir)
                else:
                    if member.name.startswith(patchRoot+'host/') and not installAllHosts:
                        # For host files we need to check if they need to be filtered. If 
                        # so (installAllHosts = False) then only install host files which
                        # match the current platform
                        if not member.name.replace(patchRoot,'').startswith(hostPaths[platform.system()]):
                            continue
                    extractFile(member, patchfile, patchRoot, destDir)
                    fileList.write(os.path.join(destDir,member.name.replace(patchRoot,''))+"\n")
                    fileList.flush()
        except (OSError,OSError),e:
            print >>sys.stderr,"Error: Could not extract file: ",e
            if contentsOnly == False:
                fileList.close()
                print >>sys.stderr,"Restoring previous system state"
                uninstallPatch(patchNum,recovery=True,meta=patchMetaDir)
            return False
        
        if contentsOnly == False:
            fileList.close()
        
        patchfile.close()
    
        if contentsOnly == False:
    
            try:
                fn = writeQConfig(patchNum, patchBase, patchDesc, patchMetaDir, destDir)
            except OSError,e:
                print >>sys.stderr,"Error: Unable to write configuration file (%s).\nAborting." % e
                print >>sys.stderr,"Restoring previous system state"
                uninstallPatch(patchNum,recovery=True,meta=patchMetaDir)
                return False
            
            if fn is not None:
                fileList = open(fileListName,"a")
                fileList.write(fn+'\n')
                fileList.close()
            
            if verbose:
                print "Recording installation information"
                print "Shiplist and other information can be found in:"
                print patchMetaDir
                
            # Record installation and timestamp (for ordering) 
            recordingFile = open(os.path.join(getInstallationBase(),"install","patches","installation.dat"),"a")
            recordingFile.write("%f %d %s\n" % (time(),int(patchNum),patchMetaDir))
            recordingFile.close()
            
            delCheckPoint(patchMetaDir)
        return True
    except KeyboardInterrupt:
        print >>sys.stderr,"Keyboard Interrupt detected." 
        print >>sys.stderr,"Restoring previous system state"
        uninstallPatch(patchNum,recovery=True,meta=patchMetaDir)
        return False



def uninstallPatch(patchNum,recovery=False, meta=None):
    """Remove one or more patches
    
    This removes a patch. Since the patches are installed in sequence
    and may overwrite each other uninstalling a patch means you have
    to remove any patches which had been installed after the one of
    interest.
    
    For each patch to be uninstalled, remove the files which had been installed,
    restore the backup and remove the config file.
    
    The special option 'recovery' is used when the installation of a
    patch failed. It must be restored from the backup and any written files 
    removed. Instead of duplicating code we use a subset of the uninstall.
    """
    # For the recovery of a failed installation we only want to remove the
    # patch which failed. This information would not have been recorded yet so
    # we can ignore this entire section
    if recovery == False:
        # Find a patch in the installation record
        recordingFile = os.path.join(getInstallationBase(),"install","patches","installation.dat")
        fil = open(recordingFile,"r")
        
        lines = sorted(fil.readlines(), key=lambda x: float(x.split()[0]), reverse=True)
        fil.close()
    
        patchlist = []
        
        # The list is reverse sorted by time. This means the first elements are the latest patches
        # to have been installed. Walk through the list recording the patch numbers found until we
        # get to the one we want. This new list represents the patches which must be uninstalled in order
        # before the one we really want is uninstalled
        for l in lines:
            (t,n,m) = l.rstrip().split()
            if int(n) != int(patchNum):
                patchlist.append(l)
            else:
                patchlist.append(l)
                break
        else:
            # The end of the list was reached. No patch was found.
            print >>sys.stderr,"Error: Patch %s could not be found" % patchNum
            return False
        
        if force == False:
            # Since this operation is potentially serious make very certain 
            # there won't be any problems. Confirm before making any changes.
            print "\nThe following patch(es) will be removed:" 
            
            for l in patchlist:
                (t,n,m) = l.split()
                backupFileName = os.path.join(m,'uninstall.dat')
                
                # Verify each of the patches to be uninstalled has a backup file
                if os.path.exists(backupFileName) == False or tarfile.is_tarfile(backupFileName) == False:
                    print >>sys.stderr,"\nError: Patch #%d does not have a valid backup file. Rollback is not possible." % int(patchNum)
                    return False                

                print "  Patch #%d" % int(n)
                
        
            if confirmation("\nWould you like to proceed? (y/n) ") == False:
                print "Patch removal aborted at user request"
                return False
    else:
        # Fake up the data for recovery: just set up for one patch
        patchlist = ["0 "+patchNum+" "+meta]
        
    curdir = os.getcwd()

    # All operations take place in the root of the file system
    os.chdir(os.sep)
    
    # Ignore keyboard interrupts for this section. There is no easy way to recover
    # if an exception is raised.
    defsig = getsignal(SIGINT)
    signal(SIGINT,SIG_IGN)
    
    for l in patchlist:
        (t,n,m) = l.split()
        backupFileName = os.path.join(m,'uninstall.dat')
        
        if recovery == False and verbose:
            print "Removing patch #%d" % int(n)
        
        # Remove the patch and restore backup
        try:
            try:
                for f in open(os.path.join(m,'filelist.dat')).readlines():
                    if os.path.exists(f.rstrip()):
                        if recovery == False and verbose:
                            print "  Removing file %s" % f.rstrip()
                        os.remove(f.rstrip())
            except IOError:
                pass
               
            # If the saved state did not indicate the backup had been completed
            # we can safely assume this backup file is not valid. It will also
            # not be required since no file extractions had taken place prior
            # to the failure.
            if recovery == False or (recovery == True and getCheckPoint(m) == 'BACKUP'):
                tar = tarfile.open(backupFileName,'r')   
                if recovery == False and verbose:
                    print "  Restoring backup...",
                tar.extractall()
                tar.close()
            if recovery == False and verbose:
                print " done"
            
            if recovery == False and verbose:
                print "  Removing metadata (%s)" % m
            for root, dirs, files in os.walk(m, topdown=False):
                for name in files:
                    os.remove(os.path.join(root, name))
                for name in dirs:
                    os.rmdir(os.path.join(root, name))
            os.rmdir(m)
        except OSError,e:
            signal(SIGINT,defsig)
            print >>sys.stderr,"Error: Unable to fully remove patch (%s)" % e
            return False

        if recovery == False:
            # Since this list represents the first N elements of lines
            # we can just remove (i.e. pop) the first element from lines
            # as we work our way forward
            del lines[0]
    
    os.chdir(curdir)
    
    # Nothing to record in recovery
    if recovery == False:
        fil = open(recordingFile,"w")
        fil.writelines(lines)
        fil.close()
    signal(SIGINT,defsig)
    return True
    

def listPatches():
    """List patches in order of installation (newest to oldest)"""
    
    recordingFile = os.path.join(getInstallationBase(),"install","patches","installation.dat")
    try:
        fil = open(recordingFile,"r")
    except IOError:
        if verbose:
            print "No patches installed"
        return False
    
    lines = sorted(fil.readlines(), key=lambda x: float(x.split()[0]), reverse=True)
    fil.close()
    
    if len(lines) == 0:
        if verbose:
            print "No patches installed"
        return False
    
    configDir = os.environ['QNX_CONFIGURATION']
    
    for patch in lines:
        (t,n,m) = patch.split()
                          
        try:
            cfgFile = open(configDir + "/qconfig/patch" + n.zfill(4) + ".xml","r")
        except (OSError,IOError):
            desc = "<config file missing>"
        else:
            for line in cfgFile:
                if line.strip().startswith(r'<name>'):
                    desc = line.strip()
                    desc = desc.replace(r'<name>Patch #%d:' % int(n),'')
                    desc = desc.replace(r'</name>','')
        print "%s   %s   %s" % (n.zfill(4),strftime("%y/%m/%d %H:%M",localtime(float(t))),desc)
    return True



if __name__ == "__main__":
    main()
