MRuby::Gem::Specification.new('mrgss_shader') do |spec|
  spec.license = 'MIT'
  spec.author  = 'mrgss developers'
  spec.add_dependency('mrgss_core')
  #----------------------------------------------------------------------------
  # Micro environment for compiling
  #----------------------------------------------------------------------------
  require 'open3'
  glew_src = "#{build_dir}/glew-1.13.0"
  
  def run_command(env, command)
    STDOUT.sync = true
    puts "mrgss: [exec] #{command}"
    Open3.popen2e(env, command) do |stdin, stdout, thread|
      print stdout.read
      fail "#{command} failed" if thread.value != 0
    end
  end
  FileUtils.mkdir_p(build_dir)
  #----------------------------------------------------------------------------
  # Download GLEW 
  #----------------------------------------------------------------------------
  if (!File.exists?("#{glew_src}.zip"))
    Dir.chdir(build_dir) do
      e = {}
      run_command e, 'wget http://ufpr.dl.sourceforge.net/project/glew/glew/1.13.0/glew-1.13.0.zip'
    end
  end
  #----------------------------------------------------------------------------
  # Unzip GLEW 
  #----------------------------------------------------------------------------
  if (!File.exists?(glew_src))
    Dir.chdir(build_dir) do
      e = {}
      run_command e, 'unzip glew-1.13.0.zip'
    end
  end
  #----------------------------------------------------------------------------
  # Unzip GLEW 
  #----------------------------------------------------------------------------
  if (!File.exists?(glew_src))
    Dir.chdir(build_dir) do
      e = {}
      run_command e, 'unzip glew-1.13.0.zip'
    end
  end
  #----------------------------------------------------------------------------
  # Build GLEW 
  #----------------------------------------------------------------------------
  e = {}
  run_command e, "make -C #{glew_src}"
  #----------------------------------------------------------------------------
  # Add GLFW to linker
  #----------------------------------------------------------------------------
  if ENV['OS'] == 'Windows_NT'
    if(File.exists?("#{glew_src}/lib/libglew32.a"))
      spec.linker.libraries << 'glew32'
    end
  else
    if(File.exists?("#{glew_src}/lib/libGLEW.a"))
      spec.linker.libraries << 'GLEW'
    end
  end
  spec.linker.library_paths.push("#{glew_src}/lib")
  spec.cc.include_paths << "#{glew_src}/include"
end
