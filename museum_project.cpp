// This has been adapted from the Vulkan tutorial

#include "MyProject.hpp"

/*


const std::string MODEL_PATH = "models/museumTri.obj";
const std::string TEXTURE_PATH = "textures/viking_room.png";



// The uniform buffer object used in this example
struct UniformBufferObject {
	alignas(16) glm::mat4 model; // alignas because instead of the RAM  we want to use the VRAM for passing down these values to the shader
	alignas(16) glm::mat4 view;
	alignas(16) glm::mat4 proj;
};

*/

struct globalUniformBufferObject {

	alignas(16) glm::mat4 view;
	alignas(16) glm::mat4 proj;
} gubo;

struct UniformBufferObject {

	alignas(16) glm::mat4 model;
} ubo;


// MAIN ! 
class MyProject : public BaseProject {
	protected:
	// Here you list all the Vulkan objects you need:
	
	// Descriptor Layouts [what will be passed to the shaders]
	DescriptorSetLayout DSLGlobal;
	DescriptorSetLayout DSLObject;

	// Pipelines [Shader couples]
	Pipeline P1;

	///////////////////// M O D E L S //////////////////////////////////////

	Model M_Walls, M_Floor, M_Frame;

	//////////////////// T E X T U R E S ///////////////////////////////////

	Texture ART, manet, matisse, monet, munch, picasso, pisarro, seurat, vgstar, vgself, cezanne, volpedo;
	Texture TX_Walls, TX_Floor;

	////////////////// D E S C R I P T O R   S E T S ///////////////////////


	DescriptorSet DS_ART, DS_manet, DS_matisse, DS_monet, DS_munch, DS_picasso, DS_pisarro, DS_seurat, DS_vgstar, DS_vgself, DS_cezanne, DS_volpedo;
	DescriptorSet DS_Walls, DS_Floor;
	DescriptorSet DS_Global;


	
	// Here you set the main application parameters
	void setWindowParameters() {
		// window size, titile and initial background
		windowWidth = 800;
		windowHeight = 600;
		windowTitle = "The Computer Graphics Museum";
		initialBackgroundColor = {1.0f, 1.0f, 1.0f, 1.0f};
		
		// Descriptor pool sizes
		uniformBlocksInPool = 15;
		texturesInPool = 14;
		setsInPool = 15;
	}
	
	// Here you load and setup all your Vulkan objects
	void localInit() {
		// Descriptor Layouts [what will be passed to the shaders]





		DSLObject.init(this, {
			// this array contains the binding:
			// first  element : the binding number
			// second element : the time of element (buffer or texture)
			// third  element : the pipeline stage where it will be used
			{0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT},
			{1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT}
			});

		DSLGlobal.init(this, { 
			{0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS}, 
			});





		// Pipelines [Shader couples]
		// The last array, is a vector of pointer to the layouts of the sets that will
		// be used in this pipeline. The first element will be set 0, and so on..
		P1.init(this, "shaders/vert.spv", "shaders/frag.spv", {&DSLObject, &DSLGlobal});


		// Models, textures and Descriptors (values assigned to the uniforms)
		M_Frame.init(this, "models/Frame_sq.obj");
		M_Walls.init(this, "models/Walls.obj");
		M_Floor .init(this, "models/Floor.obj");


		ART.init(this, "textures/ART.png");
		manet.init(this, "textures/Manet_Dejeuner.jpg");
		matisse.init(this, "textures/Matisse_theDance.jpg");
		monet.init(this, "textures/Monet-Sunrise.jpg");
		munch.init(this, "textures/Munch_Scream.jpg");
		picasso.init(this, "textures/Picasso_Guernica.jpg");
		seurat.init(this, "textures/Seurat_a_sunday.png");
		vgstar.init(this, "textures/starringNight.jpg");
		vgself.init(this, "textures/VanGogh_self.jpg");
		cezanne.init(this, "textures/theBathers_Cezanne.jpg");
		volpedo.init(this, "textures/kVolpedo_FourthEstate.jpg");

		TX_Walls.init(this, "textures/wall.jpg");
		TX_Floor.init(this, "textures/parquet.jpg");


		DescriptorSet DS_Frame, DS_Walls, DS_Floor, DS_Frame;
		DescriptorSet DS_global;

		DS_Walls.init(this, &DSLObject, {
					{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
					{1, TEXTURE, 0, &TX_Walls}
				});
		DS_Floor.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &TX_Floor}
			});

		DescriptorSet DS_ART, DS_manet, DS_matisse, DS_monet, DS_munch, DS_picasso, DS_pisarro, DS_seurat, DS_vgstar, DS_vgself, DS_cezanne, DS_volpedo;


		DS_ART.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &ART}
			});
		DS_manet.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &manet}
			});
		DS_matisse.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &matisse}
			});
		DS_monet.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &monet}
			});
		DS_munch.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &munch}
			});
		DS_picasso.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &picasso}
			});
		DS_pisarro.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &pisarro}
			});
		DS_seurat.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &seurat}
			});
		DS_vgstar.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &vgstar}
			});
		DS_vgself.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &vgself}
			});
		DS_cezanne.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &cezanne}
			});
		DS_volpedo.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &volpedo}
			});

		DS_Global.init(this, &DSLGlobal, {
					{0, UNIFORM, sizeof(globalUniformBufferObject), nullptr}
			});
	}









	// Here you destroy all the objects you created!		
	void localCleanup() {

		DS_ART.cleanup();
		DS_cezanne.cleanup();
			
		DS_manet.cleanup();
		DS_matisse.cleanup();
		DS_monet.cleanup();
		DS_munch.cleanup();
		DS_picasso.cleanup();
		DS_pisarro.cleanup();
		DS_seurat.cleanup();
		DS_vgself.cleanup();
		DS_vgstar.cleanup();
		DS_volpedo.cleanup();

		DS_Floor.cleanup();
		DS_Walls.cleanup();
		DS_Global.cleanup();


		ART.cleanup();
		cezanne.cleanup();
		manet.cleanup();
		matisse.cleanup();
		monet.cleanup();
		munch.cleanup();
		picasso.cleanup();
		pisarro.cleanup();
		seurat.cleanup();
		vgself.cleanup();
		vgstar.cleanup();
		volpedo.cleanup();
		
		TX_Walls.cleanup();
		TX_Floor.cleanup();


		M_Walls.cleanup();
		M_Floor.cleanup();
		M_Frame.cleanup();

		P1.cleanup();
		DSLGlobal.cleanup();
		DSLObject.cleanup;
	}



	DescriptorSet DS_ART, DS_manet, DS_matisse, DS_monet, DS_munch, DS_picasso, DS_pisarro, DS_seurat, DS_vgstar, DS_vgself, DS_cezanne, DS_volpedo;
	DescriptorSet DS_Walls, DS_Floor;
	DescriptorSet DS_Global;

	
	// Here it is the creation of the command buffer:
	// You send to the GPU all the objects you want to draw,
	// with their buffers and textures
	void populateCommandBuffer(VkCommandBuffer commandBuffer, int currentImage) {


				
		vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, P1.graphicsPipeline);


		////////////////////////////////////// F R A M E ///////////////////////////////////////////
		
		vkCmdBindDescriptorSets(commandBuffer,
						VK_PIPELINE_BIND_POINT_GRAPHICS,
						P1.pipelineLayout, 0, 1, &DS_Global.descriptorSets[currentImage],
						0, nullptr);


				
		VkBuffer vertexBuffers_Frame[] = {M_Frame.vertexBuffer}; // Vertex buffer for the frame of the paintings

		// property .vertexBuffer of models, contains the VkBuffer handle to its vertex buffer
		VkDeviceSize offsets_Frame[] = {0};
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers_Frame, offsets_Frame);
		// property .indexBuffer of models, contains the VkBuffer handle to its index buffer

		vkCmdBindIndexBuffer(commandBuffer, M_Frame.indexBuffer, 0, VK_INDEX_TYPE_UINT32);

		////////////////////////////////////// W A L L S ///////////////////////////////////////////

		// property .pipelineLayout of a pipeline contains its layout.
		// property .descriptorSets of a descriptor set contains its elements.
		vkCmdBindDescriptorSets(commandBuffer,
						VK_PIPELINE_BIND_POINT_GRAPHICS,
						P1.pipelineLayout, 0, 1, &DS_Walls.descriptorSets[currentImage],
						0, nullptr);
						
		// property .indices.size() of models, contains the number of triangles * 3 of the mesh.
		vkCmdDrawIndexed(commandBuffer,
					static_cast<uint32_t>(M_Walls.indices.size()), 1, 0, 0, 0);

		VkBuffer vertexBuffers_Walls[] = { M_Walls.vertexBuffer };
		VkDeviceSize offsets_Walls[] = {0};

		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers_Walls, offsets_Walls);


		////////////////////////////////////// F L O O R ///////////////////////////////////////////

		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 0, 1, &DS_Floor.descriptorSets[currentImage],
			0, nullptr);

		// property .indices.size() of models, contains the number of triangles * 3 of the mesh.
		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Floor.indices.size()), 1, 0, 0, 0);

		VkBuffer vertexBuffers_Floor[] = { M_Floor.vertexBuffer };
		VkDeviceSize offsets_Floor[] = { 0 };

		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers_Floor, offsets_Floor);














	}

	// Here is where you update the uniforms.
	// Very likely this will be where you will be writing the logic of your application.
	void updateUniformBuffer(uint32_t currentImage) {
		static auto startTime = std::chrono::high_resolution_clock::now();
		auto currentTime = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration<float, std::chrono::seconds::period>
					(currentTime - startTime).count();
					
					
		UniformBufferObject ubo{};
		ubo.model = glm::rotate(glm::mat4(1.0f),
								time * glm::radians(90.0f),
								glm::vec3(0.0f, 0.0f, 1.0f));
		ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f),
							   glm::vec3(0.0f, 0.0f, 0.0f),
							   glm::vec3(0.0f, 0.0f, 1.0f));
		ubo.proj = glm::perspective(glm::radians(45.0f),
						swapChainExtent.width / (float) swapChainExtent.height,
						0.1f, 10.0f);
		ubo.proj[1][1] *= -1;
		
		void* data;

		// Here is where you actually update your uniforms
		vkMapMemory(device, DS1.uniformBuffersMemory[0][currentImage], 0,
							sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(device, DS1.uniformBuffersMemory[0][currentImage]);
	}	
};

// This is the main: probably you do not need to touch this!
int main() {
    MyProject app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}