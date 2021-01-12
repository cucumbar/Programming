# -*- mode: python ; coding: utf-8 -*-

block_cipher = None


a = Analysis(['Lines.py'],
             pathex=['C:\\Users\\Михондрус\\myGitRepoCloned\\Programming\\Lab\\03\\linesfiles'],
             binaries=[],
             datas=[('resources/ball-red.png', 'resources'), 
	('resources/ball-red.png', 'resources'), 
	('resources/ball-violet.png', 'resources'),
	('resources/ball-green.png', 'resources'),
	('resources/ball-pink.png', 'resources'),
	('resources/ball-yellow.png', 'resources'),
	('resources/ball-blue.png', 'resources'),
	('resources/ball-aqua.png', 'resources'),
	('resources/cell-bgr.png', 'resources')],
             hiddenimports=[],
             hookspath=[],
             runtime_hooks=[],
             excludes=[],
             win_no_prefer_redirects=False,
             win_private_assemblies=False,
             cipher=block_cipher,
             noarchive=False)
pyz = PYZ(a.pure, a.zipped_data,
             cipher=block_cipher)
exe = EXE(pyz,
          a.scripts,
          a.binaries,
          a.zipfiles,
          a.datas,
          [],
          name='Lines',
          debug=False,
          bootloader_ignore_signals=False,
          strip=False,
          upx=True,
          upx_exclude=[],
          runtime_tmpdir=None,
          console=True,
	  icon="C:\\Users\\Михондрус\\myGitRepoCloned\\Programming\\Lab\\03\\linesfiles\\icon.ico")
