---


---

<h1 id="libcl">Libcl</h1>
<h3 id="this-a-tiny-opencl-librarytemplate-to-make-starting-and-working-with-opencl-easier.">This a tiny OpenCL library/template to make starting and working with OpenCL easier.</h3>
<p><strong>Only MacOS supported natively - Windows\Linux users will have to build from sources and configure OpenCL includes!</strong></p>
<p>This repo also contains test <em>main.c</em> the project file, <em>kernel</em> and <em>Makefile</em> to compile the project with.</p>
<p><strong>You should educate yourself closely with the in-code comments as well as the code.</strong></p>
<h2 id="changelog--latest-marked-in-bold">Changelog  (latest marked in bold)</h2>
<ul>
<li><strong>Updated reuse logic - please refer to the in-code comment section in the <code>cl_clean_up();</code> function for information on how to reuse a kernel + work with multiple kernels</strong></li>
<li>Now you have an option to reuse your kernel and program, by cleaning only memory objects assosiated with it via invoking <code>cl_clean_up(t_cl *cl)</code> P.S. allocations inside elements structure aren’t freed</li>
<li>Memory leaks are solved (you should still check tho, just in case)</li>
<li>Now you can learn how to pass a user-defined structure into the kernel</li>
<li>Error handling implemetned</li>
<li>Now you can create a header for the kernel file and include it into the program build</li>
</ul>
<h2 id="tiny-terminology">Tiny terminology</h2>
<ul>
<li><strong>OpenCL (Open Computing Language)</strong> - framework for a parralel execution of programs on different compute devices (CPUs, GPUs)</li>
<li><strong>Kernel (vector)</strong> - A function which will be sent and executed on a compute device.
<ul>
<li>These files have a <code>.cl</code> extension.</li>
</ul>
</li>
<li><strong>NDRange</strong> - total size of a <em>compute grid</em> - the total amount of calculations to be performed.</li>
<li><strong>Work Group</strong> - a subset of the <em>NDRange</em> which divides total workload into equal groups.</li>
</ul>
<h2 id="test-project"><strong>Test project</strong></h2>
<p>Test project will perform 1024 additions <code>(0 + 1024, 1 + 1023, ...., 1023 + 1)</code> from input vectors, adding 4 and 2 from a structure, passed as an argument to every result on OpenCL and print the results.</p>
<p>For example, one of the calculations will be this:<br>
<code>1 + 1023 + 4 + 2 = 1030</code></p>
<h2 id="how-to-use"><strong>How to use</strong></h2>
<ul>
<li>Library itself is withing the <strong>libcl</strong> folder.</li>
<li>Compile the project using <strong>Makefile</strong> in the root of the repo with <code>make</code>.</li>
<li>This library operates using structures, which contain all the necessary data, including links to the input and output parameters, the name of a kernel file, as well as the NDRange value.
<ul>
<li>Your structures should be placed inside the <strong>cl_user_structs.h</strong> file and initialized properly.</li>
</ul>
</li>
<li><strong><a href="http://kernel.cl">kernel.cl</a></strong> is a file containing instructions to be executed in on the OpenCL device.
<ul>
<li>Those should be placed in the <strong>kernels</strong> folder at the root of the project.</li>
</ul>
</li>
<li>Header files, which you will use inside your kernels are placed into the <strong>kernel_includes</strong> directory</li>
</ul>
<h4 id="for-a-quick-start-using-pre-configured-functions-and-structures">For a quick start using pre-configured functions and structures:</h4>
<ul>
<li>Call <code>init_opencl_structs</code> to initialize all the service data.</li>
<li>This function will return a pointer to your <code>t_cl</code> struct.</li>
<li>Call <code>init_opencl_elems</code> to initialize a structure for your data.
<ul>
<li>This function will accept the <em>NDRange</em>, <em>name of the kernel file</em> and the <em>name of the function to be processed within the kernel file</em> as it’s arguments and return a pointer to a <code>t_elems</code> struct.</li>
</ul>
</li>
<li>Create input methods for the data.</li>
<li>Call <code>opencl_calc</code> function to perform the OpenCL calculation.
<ul>
<li>This function will accept a <em>pointer to your <code>t_cl</code> struct</em> and a <em>pointer to your <code>t_elems</code> struct</em> as it’s arguments and will return a pointer to a memory area, containing the result of a calculation.</li>
</ul>
</li>
<li>Use the result.</li>
<li>Call <code>cl_clean_up</code> to clean up all the service data.
<ul>
<li>This function accepts a <em>pointer to your <code>t_cl</code> struct</em>.</li>
</ul>
</li>
<li>Call <code>cl_clean_structs</code> to clean up structure containing your data.
<ul>
<li>This function accepts a pointer to your <code>t_elems</code> struct*.</li>
</ul>
</li>
</ul>
<p><strong>Read the in-code comments and alter the functions/headers  according to the template to fit your needs!</strong></p>
<h2 id="function-descriptions">Function descriptions</h2>
<p><strong>Notes:</strong></p>
<ul>
<li><em>Fresh</em> means freshly allocated with <code>malloc</code></li>
<li><em>Cleans up</em> means <em>releases, flushes, finishes</em> or <em>frees</em> given areas</li>
</ul>

<table>
<thead>
<tr>
<th>Declaration</th>
<th>Description</th>
<th>Return</th>
</tr>
</thead>
<tbody>
<tr>
<td></td>
<td></td>
<td></td>
</tr>
<tr>
<td><code>t_cl *init_opencl_structs(void);</code></td>
<td>Initializes service structures</td>
<td>Pointer to fresh <code>t_cl</code> struct</td>
</tr>
<tr>
<td><code>void init_user_cl_structs(t_cl *cl);</code></td>
<td>Initializes structures for user memory objects</td>
<td>None</td>
</tr>
<tr>
<td><code>t_elems *init_opencl_elems(int NDRange, char *kernel_name, char *function_name);</code></td>
<td>Initializes structures for user data</td>
<td>Pointer to fresh <code>t_elems</code> struct</td>
</tr>
<tr>
<td><code>int *opencl_calc(t_cl *cl, t_elems *elems);</code></td>
<td>Performs an OpenCL calculation. <strong>HAVE A LOOK AT THE <em>FINAL NOTES</em> SECTION AT THE END OF THIS GUIDE</strong></td>
<td>Pointer to a memory area containing results fo the calculation</td>
</tr>
<tr>
<td><code>void load_kernel_src_code(char *kernel_name, t_cl *cl);</code></td>
<td>Loads kernel source code into the <em>cl structure</em></td>
<td>None</td>
</tr>
<tr>
<td><code>void get_cl_info(t_cl *cl);</code></td>
<td>Queries available OpenCL platforms &amp; devices</td>
<td>None</td>
</tr>
<tr>
<td><code>void create_context_coms_queue(t_cl *cl);</code></td>
<td>Creates an OpenCl context &amp; command queue</td>
<td>None</td>
</tr>
<tr>
<td><code>void create_buffs(t_cl *cl, int *a, int *b, int NDRange);</code></td>
<td>Creates memory buffers on the device for each input vector (a &amp; b)</td>
<td>None</td>
</tr>
<tr>
<td><code>void cpy_to_buffs(t_cl *cl, int *a, int *b, int NDRange);</code></td>
<td>Copies lists A and B to their respective memory buffers</td>
<td>None</td>
</tr>
<tr>
<td><code>void prep_kernel(t_cl *cl, char *kernel_ft);</code></td>
<td>Creates a program from the kernel source, builds the program &amp; creates OpenCL kernel</td>
<td>None</td>
</tr>
<tr>
<td><code>void set_kernel_args(t_cl *cl);</code></td>
<td>Sets kernel arguments</td>
<td>None</td>
</tr>
<tr>
<td><code>void exec_kernel(t_cl *cl, int NDRange);</code></td>
<td>Executes OpenCL kernel on the given list</td>
<td>None</td>
</tr>
<tr>
<td><code>int *read_buff(t_cl *cl, int NDRange);</code></td>
<td>Allocates memory for the local variable <em>res</em> containing results of a calculation and reads the memory buffer <em>C</em> on the device to the local variable <em>res</em></td>
<td>Pointer to the memory area containing results of a calculation</td>
</tr>
<tr>
<td><code>void cl_clean_up(t_cl *cl);</code></td>
<td>Releases assosiated memory objects. Device, platform, command queue, program, kernel and context are saved for reuse</td>
<td>None</td>
</tr>
<tr>
<td><code>void cl_clean_up_all(t_cl *cl);</code></td>
<td>Cleans up all OpenCL service data _(This function should be used after <code>cl_clean_up()</code>, after you have done all the work with your program and are ready to get rid of it).</td>
<td>None</td>
</tr>
<tr>
<td><code>void cl_clean_mem_objs(t_cl *cl);</code></td>
<td>Cleans up OpenCL memory areas</td>
<td>None</td>
</tr>
<tr>
<td><code>void cl_clean_structs(t_cl *cl, t_elems *elems);</code></td>
<td>Cleans up structures</td>
<td>None</td>
</tr>
</tbody>
</table><h2 id="learning-resources">Learning resources</h2>
<ul>
<li><a href="https://www.drdobbs.com/parallel/a-gentle-introduction-to-opencl/231002854?pgno=3">Dr. Dobb’s</a> introduction to OpenCL</li>
<li><a href="https://www.fz-juelich.de/SharedDocs/Downloads/IAS/JSC/EN/slides/opencl/opencl-03-basics.pdf?__blob=publicationFile">Jülich Forschungszentrum</a> lecture slides on OpenCL basics</li>
<li><a href="https://developer.apple.com/library/archive/documentation/Performance/Conceptual/OpenCL_MacProgGuide/Introduction/Introduction.html#//apple_ref/doc/uid/TP40008312-CH1-SW1">Apple Developer</a> guide on OpenCL for MacOS</li>
<li><a href="https://cmp.phys.msu.ru/sites/default/files/OpenCL.pdf">OpenCL - Open Language for Parralel Programs (Russian)</a> - introductory course into OpenCL</li>
</ul>
<h2 id="final-notes">Final notes</h2>
<ul>
<li><strong>You will see that the <code>main();</code> invokes the <code>opencl_calc();</code> function to perform the calculation. Even though you can (and should!) use this function for a basic one-off application, I would advise you refrain from using it for any serious work, as it is more a layout of the OpenCL calls order, rather than a proper function</strong></li>
<li>If you choose to compile from sources (without <strong>Makefile</strong>), don’t forget the <code>-framework OpenCL</code> flag.</li>
<li>Be informed, that this project uses <code>&lt;stdio.h&gt;</code> and <code>&lt;stdlib&gt;</code> includes.</li>
</ul>
<h2 id="credit">Credit</h2>
<p>This project is based on the <a href="https://github.com/smistad/OpenCL-Getting-Started">OpenCL-Getting-Started</a> project by Erik Smistad (@smistad).</p>

