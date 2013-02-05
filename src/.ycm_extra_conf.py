# Specify compiler flags for the YouCompleteMe plugin in Vim.
def FlagsForFile(filename):
  return {
    'flags': open('.clang_complete', 'r').readlines(),
    'do_cache': True
  }
