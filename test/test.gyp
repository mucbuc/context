{
	'includes':[
		'lib/context/def/base.gypi',
		'lib/traverse/def/base.gypi',
		'plank/def/mac-targets.gypi',
		'plank/def/cpp11.gypi'
	],#inclues
	'target_defaults': {
		'target_name': 'test', 
		'type': 'executable',
		'sources': [
			'src/main.cpp'
		], #sources
		'include_dirs': [
			'plank/src/',
			'.'
		], #include_dirs		
	}, #target_defaults
}