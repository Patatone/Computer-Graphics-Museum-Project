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
	Texture ART_card, manet_card, matisse_card, monet_card, munch_card, picasso_card, pisarro_card, seurat_card, vgstar_card, vgself_card, cezanne_card, volpedo_card;
	Texture TX_Walls, TX_Floor;

	////////////////// D E S C R I P T O R   S E T S ///////////////////////


	DescriptorSet DS_ART, DS_manet, DS_matisse, DS_monet, DS_munch, DS_picasso, DS_pisarro, DS_seurat, DS_vgstar, DS_vgself, DS_cezanne, DS_volpedo;
	DescriptorSet DS_ART_card, DS_manet_card, DS_matisse_card, DS_monet_card, DS_munch_card, DS_picasso_card, DS_pisarro_card, DS_seurat_card, DS_vgstar_card, DS_vgself_card, DS_cezanne_card, DS_volpedo_card;
	DescriptorSet DS_Walls, DS_Floor;

	DescriptorSet DS_Global;


	
	// Here you set the main application parameters
	void setWindowParameters() {
		// window size, titile and initial background
		windowWidth = 1600;
		windowHeight = 900;
		windowTitle = "The Computer Graphics Museum";
		initialBackgroundColor = {1.0f, 1.0f, 1.0f, 1.0f};
		
		// Descriptor pool sizes
		uniformBlocksInPool = 27;
		texturesInPool = 26;
		setsInPool = 27;
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
		P1.init(this, "shaders/vert.spv", "shaders/frag.spv", {&DSLGlobal, &DSLObject});


		// Models, textures and Descriptors (values assigned to the uniforms)
		
		// W A L L S //

		M_Walls.init(this, "models/Walls.obj");
		TX_Walls.init(this, "textures/wall.png");
		DS_Walls.init(this, &DSLObject, {
					{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
					{1, TEXTURE, 0, &TX_Walls}
				});

		// F L O O R //

		M_Floor .init(this, "models/Floor.obj");
		TX_Floor.init(this, "textures/parquet.png");
		DS_Floor.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &TX_Floor}
			}); 

		////////////////////////////////////// F R A M E S //////////////////////////////////////

		M_Frame.init(this, "models/Rectangle.obj");


		// A R T //

		ART.init(this, "textures/ART.png");
		DS_ART.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &ART}
			});

		ART_card.init(this, "textures/ART_card.png");
		DS_ART_card.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &ART_card}
			});

		// M A N E T //

		manet.init(this, "textures/Manet_Dejeuner.png");
		DS_manet.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &manet}
			});

		manet_card.init(this, "textures/Manet_Dejeuner_card.png");
		DS_manet_card.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &manet_card}
			});

		// M A T I S S E //

		matisse.init(this, "textures/Matisse_theDance.png");
		DS_matisse.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &matisse}
			});

		matisse_card.init(this, "textures/Matisse_theDance_card.png");
		DS_matisse_card.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &matisse_card}
			});

		// M O N E T //

		monet.init(this, "textures/Monet-Sunrise.png");
		DS_monet.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &monet}
			});

		monet_card.init(this, "textures/Monet-Sunrise_card.png");
		DS_monet_card.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &monet_card}
			});

		// M U N C H //

		munch.init(this, "textures/Munch_Scream.png");
		DS_munch.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &munch}
			});

		munch_card.init(this, "textures/Munch_Scream_card.png");
		DS_munch_card.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &munch_card}
			});

		// P I C A S S O // 

		picasso.init(this, "textures/Picasso_Guernica.png");
		DS_picasso.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &picasso}
			});

		picasso_card.init(this, "textures/Picasso_Guernica_card.png");
		DS_picasso_card.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &picasso_card}
			});

		// P I S A R R O //

		pisarro.init(this, "textures/pisarro_boulevard_monmarte.png");
		DS_pisarro.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &pisarro}
			});

		pisarro_card.init(this, "textures/pisarro_boulevard_monmarte_card.png");
		DS_pisarro_card.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &pisarro_card}
			});

		// S E U R A T //

		seurat.init(this, "textures/Seurat_a_sunday.png");
		DS_seurat.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &seurat}
			});

		seurat_card.init(this, "textures/Seurat_a_sunday_card.png");
		DS_seurat_card.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &seurat_card}
			});

		// V A N  G O G H  S T A R R Y //

		vgstar.init(this, "textures/starringNight.png");
		DS_vgstar.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &vgstar}
			});

		vgstar_card.init(this, "textures/starringNight_card.png");
		DS_vgstar_card.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &vgstar_card}
			});

		// V A N  G O G H  S E L F //

		vgself.init(this, "textures/VanGogh_self.png");	
		DS_vgself.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &vgself}
			});

		vgself_card.init(this, "textures/VanGogh_self_card.png");
		DS_vgself_card.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &vgself_card}
			});

		// C E Z A N N E //

		cezanne.init(this, "textures/theBathers_Cezanne.png");
		DS_cezanne.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &cezanne}
			});

		cezanne_card.init(this, "textures/theBathers_Cezanne_card.png");
		DS_cezanne_card.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &cezanne_card}
			});

		// V O L P E D O //

		volpedo.init(this, "textures/Volpedo_FourthEstate.png");
		DS_volpedo.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &volpedo}
			});

		volpedo_card.init(this, "textures/Volpedo_FourthEstate_card.png");
		DS_volpedo_card.init(this, &DSLObject, {
						{0, UNIFORM, sizeof(UniformBufferObject), nullptr},
						{1, TEXTURE, 0, &volpedo_card}
			});

		// G L O B A L //


		DS_Global.init(this, &DSLGlobal, { 
						{0, UNIFORM, sizeof(globalUniformBufferObject), nullptr}, 
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

		DS_ART_card.cleanup();
		DS_cezanne_card.cleanup();
		DS_manet_card.cleanup();
		DS_matisse_card.cleanup();
		DS_monet_card.cleanup();
		DS_munch_card.cleanup();
		DS_picasso_card.cleanup();
		DS_pisarro_card.cleanup();
		DS_seurat_card.cleanup();
		DS_vgself_card.cleanup();
		DS_vgstar_card.cleanup();
		DS_volpedo_card.cleanup();

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


		ART_card.cleanup();
		cezanne_card.cleanup();
		manet_card.cleanup();
		matisse_card.cleanup();
		monet_card.cleanup();
		munch_card.cleanup();
		picasso_card.cleanup();
		pisarro_card.cleanup();
		seurat_card.cleanup();
		vgself_card.cleanup();
		vgstar_card.cleanup();
		volpedo_card.cleanup();		
		
		TX_Walls.cleanup();
		TX_Floor.cleanup();


		M_Walls.cleanup();
		M_Floor.cleanup();
		M_Frame.cleanup();

		P1.cleanup();
		DSLGlobal.cleanup();
		DSLObject.cleanup();

	}



	
	

	
	// Here it is the creation of the command buffer:
	// You send to the GPU all the objects you want to draw,
	// with their buffers and textures
	void populateCommandBuffer(VkCommandBuffer commandBuffer, int currentImage) {


				
		vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, P1.graphicsPipeline);

		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 0, 1, &DS_Global.descriptorSets[currentImage],
			0, nullptr);


		

		//////////////////////////////////// W A L L S ///////////////////////////////////////////

		// property .pipelineLayout of a pipeline contains its layout.
		// property .descriptorSets of a descriptor set contains its elements.

		VkBuffer vertexBuffers_Walls[] = { M_Walls.vertexBuffer };
		VkDeviceSize offsets_Walls[] = {0};

		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers_Walls, offsets_Walls);

		vkCmdBindIndexBuffer(commandBuffer, M_Walls.indexBuffer, 0,
			VK_INDEX_TYPE_UINT32);

		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_Walls.descriptorSets[currentImage],
			0, nullptr);
						
		// property .indices.size() of models, contains the number of triangles * 3 of the mesh.
		vkCmdDrawIndexed(commandBuffer,
					static_cast<uint32_t>(M_Walls.indices.size()), 1, 0, 0, 0);

		
		//////////////////////////////////////// F L O O R ///////////////////////////////////////////

		VkBuffer vertexBuffers_Floor[] = { M_Floor.vertexBuffer };
		VkDeviceSize offsets_Floor[] = { 0 };

		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers_Floor, offsets_Floor);

		vkCmdBindIndexBuffer(commandBuffer, M_Floor.indexBuffer, 0,
			VK_INDEX_TYPE_UINT32);

		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_Floor.descriptorSets[currentImage],
			0, nullptr);

		// property .indices.size() of models, contains the number of triangles * 3 of the mesh.
		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Floor.indices.size()), 1, 0, 0, 0);


		//////////////////////////////////////// F R A M E S ///////////////////////////////////////////

		VkBuffer vertexBuffers_Frames[] = { M_Frame.vertexBuffer };
		VkDeviceSize offsets_Frames[] = { 0 };

		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers_Frames, offsets_Frames);

		vkCmdBindIndexBuffer(commandBuffer, M_Frame.indexBuffer, 0,
			VK_INDEX_TYPE_UINT32);


		// A R T //

		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_ART.descriptorSets[currentImage],
			0, nullptr);

		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Frame.indices.size()), 1, 0, 0, 0);

		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_ART_card.descriptorSets[currentImage],
			0, nullptr);

		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Frame.indices.size()), 1, 0, 0, 0);



		// M A N E T //

		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_manet.descriptorSets[currentImage],
			0, nullptr);

		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Frame.indices.size()), 1, 0, 0, 0);

		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_manet_card.descriptorSets[currentImage],
			0, nullptr);

		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Frame.indices.size()), 1, 0, 0, 0);

		// M A T I S S E //

		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_matisse.descriptorSets[currentImage],
			0, nullptr);

		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Frame.indices.size()), 1, 0, 0, 0);
		
		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_matisse_card.descriptorSets[currentImage],
			0, nullptr);

		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Frame.indices.size()), 1, 0, 0, 0);

		// M O N E T //


		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_monet.descriptorSets[currentImage],
			0, nullptr);

		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Frame.indices.size()), 1, 0, 0, 0);

		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_monet_card.descriptorSets[currentImage],
			0, nullptr);

		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Frame.indices.size()), 1, 0, 0, 0);

		// M U N C H //


		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_munch.descriptorSets[currentImage],
			0, nullptr);

		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Frame.indices.size()), 1, 0, 0, 0);

		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_munch_card.descriptorSets[currentImage],
			0, nullptr);

		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Frame.indices.size()), 1, 0, 0, 0);

		// P I C A S S O //

		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_picasso.descriptorSets[currentImage],
			0, nullptr);

		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Frame.indices.size()), 1, 0, 0, 0);

		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_picasso_card.descriptorSets[currentImage],
			0, nullptr);

		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Frame.indices.size()), 1, 0, 0, 0);

		// P I S A R R O //

		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_pisarro.descriptorSets[currentImage],
			0, nullptr);

		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Frame.indices.size()), 1, 0, 0, 0);

		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_pisarro_card.descriptorSets[currentImage],
			0, nullptr);

		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Frame.indices.size()), 1, 0, 0, 0);

		// S E U R A T //

		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_seurat.descriptorSets[currentImage],
			0, nullptr);

		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Frame.indices.size()), 1, 0, 0, 0);

		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_seurat_card.descriptorSets[currentImage],
			0, nullptr);

		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Frame.indices.size()), 1, 0, 0, 0);

		// V A N  G O G H   S T A R //

		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_vgstar.descriptorSets[currentImage],
			0, nullptr);

		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Frame.indices.size()), 1, 0, 0, 0);

		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_vgstar_card.descriptorSets[currentImage],
			0, nullptr);

		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Frame.indices.size()), 1, 0, 0, 0);

		// V A N  G O G H   S E L F //

		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_vgself.descriptorSets[currentImage],
			0, nullptr);

		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Frame.indices.size()), 1, 0, 0, 0);

		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_vgself_card.descriptorSets[currentImage],
			0, nullptr);

		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Frame.indices.size()), 1, 0, 0, 0);


		// C E Z A N N E //

		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_cezanne.descriptorSets[currentImage],
			0, nullptr);

		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Frame.indices.size()), 1, 0, 0, 0);

		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_cezanne_card.descriptorSets[currentImage],
			0, nullptr);

		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Frame.indices.size()), 1, 0, 0, 0);

		// V O L P E D O //

		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_volpedo.descriptorSets[currentImage],
			0, nullptr);

		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Frame.indices.size()), 1, 0, 0, 0);

		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			P1.pipelineLayout, 1, 1, &DS_volpedo_card.descriptorSets[currentImage],
			0, nullptr);

		vkCmdDrawIndexed(commandBuffer,
			static_cast<uint32_t>(M_Frame.indices.size()), 1, 0, 0, 0);

	}





	// Here is where you update the uniforms.
	// Very likely this will be where you will be writing the logic of your application.
	void updateUniformBuffer(uint32_t currentImage) {
		static auto startTime = std::chrono::high_resolution_clock::now();
		auto currentTime = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration<float, std::chrono::seconds::period>
					(currentTime - startTime).count();

		static struct CameraAngle {
		    float x = 0.0f;
			float y = 0.0f;
			float z = 0.0f;
		} CamAngle;

		static struct CameraPosition {
			float x = 1.0f;
			float y = -0.5f;
			float z = 1.0f;
		} CamPos;

		const float W_speed = 0.001;
		const float S_speed = 0.0006;

		const float A_speed = 0.0004;
		const float D_speed = 0.0004;

		const float rot_speed_v = 0.02; // vertical rotation
		const float rot_speed_h = 0.06; // horizontal rotation

		glm::mat4 one_mat = glm::mat4(1.0f);

		static glm::vec3 Translation = glm::vec3(0.0f, 0.0f, 0.0f);

		////////////////////////// C O N T R O L S //////////////////////////

		if (glfwGetKey(window, GLFW_KEY_W)) {
		
			CamPos.x -= W_speed * sin(glm::radians(CamAngle.y));
			CamPos.z += W_speed * cos(glm::radians(CamAngle.y));
			
			

		}
		if (glfwGetKey(window, GLFW_KEY_A)) {

			CamPos.z += A_speed * sin(glm::radians(CamAngle.y));
			CamPos.x += W_speed * cos(glm::radians(CamAngle.y));
		
		}
		if (glfwGetKey(window, GLFW_KEY_D)) {

			CamPos.z -= A_speed * sin(glm::radians(CamAngle.y));
			CamPos.x -= W_speed * cos(glm::radians(CamAngle.y));
	
		}
		if (glfwGetKey(window, GLFW_KEY_S)) {

			CamPos.x += S_speed * sin(glm::radians(CamAngle.y));
			CamPos.z -= S_speed * cos(glm::radians(CamAngle.y));

		}

		if (glfwGetKey(window, GLFW_KEY_UP)) {

			CamAngle.x -= rot_speed_v;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT)) {

			CamAngle.y -= rot_speed_h;
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT)) {

			CamAngle.y += rot_speed_h;
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN)) {

			CamAngle.x += rot_speed_v;
		}

		globalUniformBufferObject gubo{};
		UniformBufferObject ubo{};

		void* data;		


		gubo.view = glm::rotate(glm::mat4(1.0f), glm::radians(CamAngle.x), glm::vec3(1, 0, 0)) *
					glm::rotate(glm::mat4(1.0f), glm::radians(CamAngle.y), glm::vec3(0, 1, 0)) *
					glm::rotate(glm::mat4(1.0f), glm::radians(CamAngle.z), glm::vec3(0, 0, 1)) *
					glm::translate(glm::mat4(1), glm::vec3(CamPos.x, CamPos.y, CamPos.z));


		gubo.proj = glm::perspective(glm::radians(45.0f),
					swapChainExtent.width / (float)swapChainExtent.height, 0.1f, 10.0f);

		gubo.proj[1][1] *= -1;

		// GLOBAL DESCRIPTOR SET
		vkMapMemory(device, DS_Global.uniformBuffersMemory[0][currentImage], 0,
							sizeof(gubo), 0, &data);
		memcpy(data, &gubo, sizeof(gubo));
		vkUnmapMemory(device, DS_Global.uniformBuffersMemory[0][currentImage]);

		// Placing Floor

		ubo.model = glm::mat4(1.0f);

		vkMapMemory(device, DS_Floor.uniformBuffersMemory[0][currentImage], 0,
			sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(device, DS_Floor.uniformBuffersMemory[0][currentImage]);

		// Placing Walls

		ubo.model = glm::mat4(1.0f);

		vkMapMemory(device, DS_Walls.uniformBuffersMemory[0][currentImage], 0,
			sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(device, DS_Walls.uniformBuffersMemory[0][currentImage]);

		////////////////////////// P I C T U R E S //////////////////////////

		// A R T //


		
		ubo.model = one_mat * glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f, 1.0f, 1.99f));
		ubo.model = ubo.model * glm::rotate(glm::mat4(1.0), glm::radians(180.0f), glm::vec3(0, 1, 0)) * glm::scale(one_mat, glm::vec3(0.4, 0.4, 0.4));

		vkMapMemory(device, DS_ART.uniformBuffersMemory[0][currentImage], 0,
			sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(device, DS_ART.uniformBuffersMemory[0][currentImage]);

		ubo.model = one_mat * glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f, 0.35f, 1.99f));
		ubo.model = ubo.model * glm::rotate(glm::mat4(1.0), glm::radians(180.0f), glm::vec3(0, 1, 0)) * glm::scale(one_mat, glm::vec3(0.1, 0.1, 0.1));

		vkMapMemory(device, DS_ART_card.uniformBuffersMemory[0][currentImage], 0,
			sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(device, DS_ART_card.uniformBuffersMemory[0][currentImage]);


		// M A N E T //

		ubo.model = one_mat * glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f, 1.0f, -1.99f));
		ubo.model = ubo.model * glm::rotate(glm::mat4(1.0), glm::radians(0.0f), glm::vec3(0, 1, 0)) * glm::scale(one_mat, glm::vec3(0.4, 0.4, 0.4));

		vkMapMemory(device, DS_manet.uniformBuffersMemory[0][currentImage], 0,
			sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(device, DS_manet.uniformBuffersMemory[0][currentImage]);
		
		ubo.model = one_mat * glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f, 0.35f,- 1.99f));
		ubo.model = ubo.model * glm::rotate(glm::mat4(1.0), glm::radians(0.0f), glm::vec3(0, 1, 0)) * glm::scale(one_mat, glm::vec3(0.1, 0.1, 0.1));

		vkMapMemory(device, DS_manet_card.uniformBuffersMemory[0][currentImage], 0,
			sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(device, DS_manet_card.uniformBuffersMemory[0][currentImage]);


		// M A T I S S E // 

		ubo.model = one_mat * glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 1.0f, 1.99f));
		ubo.model = ubo.model * glm::rotate(glm::mat4(1.0), glm::radians(180.0f), glm::vec3(0, 1, 0)) * glm::scale(one_mat, glm::vec3(0.4, 0.4, 0.4));

		vkMapMemory(device, DS_matisse.uniformBuffersMemory[0][currentImage], 0,
			sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(device, DS_matisse.uniformBuffersMemory[0][currentImage]);

		ubo.model = one_mat * glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.35f, 1.99f));
		ubo.model = ubo.model * glm::rotate(glm::mat4(1.0), glm::radians(180.0f), glm::vec3(0, 1, 0)) * glm::scale(one_mat, glm::vec3(0.1, 0.1, 0.1));

		vkMapMemory(device, DS_matisse_card.uniformBuffersMemory[0][currentImage], 0,
			sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(device, DS_matisse_card.uniformBuffersMemory[0][currentImage]);


		// M O N E T //

		ubo.model = one_mat * glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 1.0f, -1.99f));
		ubo.model = ubo.model * glm::rotate(glm::mat4(1.0), glm::radians(0.0f), glm::vec3(0, 1, 0)) * glm::scale(one_mat, glm::vec3(0.4, 0.4, 0.4));

		vkMapMemory(device, DS_monet.uniformBuffersMemory[0][currentImage], 0,
			sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(device, DS_monet.uniformBuffersMemory[0][currentImage]);

		ubo.model = one_mat * glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.35f, -1.99f));
		ubo.model = ubo.model * glm::rotate(glm::mat4(1.0), glm::radians(0.0f), glm::vec3(0, 1, 0)) * glm::scale(one_mat, glm::vec3(0.1, 0.1, 0.1));

		vkMapMemory(device, DS_monet_card.uniformBuffersMemory[0][currentImage], 0,
			sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(device, DS_monet_card.uniformBuffersMemory[0][currentImage]);


		// M U N C H //

		ubo.model = one_mat * glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.99f));
		ubo.model = ubo.model * glm::rotate(glm::mat4(1.0), glm::radians(180.0f), glm::vec3(0, 1, 0)) * glm::scale(one_mat, glm::vec3(0.18, 0.4, 0.4));

		vkMapMemory(device, DS_munch.uniformBuffersMemory[0][currentImage], 0,
			sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(device, DS_munch.uniformBuffersMemory[0][currentImage]);

		ubo.model = one_mat * glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.35f, 1.99f));
		ubo.model = ubo.model * glm::rotate(glm::mat4(1.0), glm::radians(180.0f), glm::vec3(0, 1, 0)) * glm::scale(one_mat, glm::vec3(0.1, 0.1, 0.1));

		vkMapMemory(device, DS_munch_card.uniformBuffersMemory[0][currentImage], 0,
			sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(device, DS_munch_card.uniformBuffersMemory[0][currentImage]);


		// P I C A S S O //

		ubo.model = one_mat * glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, -1.99f));
		ubo.model = ubo.model * glm::rotate(glm::mat4(1.0), glm::radians(0.0f), glm::vec3(0, 1, 0)) * glm::scale(one_mat, glm::vec3(0.4, 0.4, 0.4));

		vkMapMemory(device, DS_picasso.uniformBuffersMemory[0][currentImage], 0,
			sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(device, DS_picasso.uniformBuffersMemory[0][currentImage]);

		ubo.model = one_mat * glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.35f, -1.99f));
		ubo.model = ubo.model * glm::rotate(glm::mat4(1.0), glm::radians(0.0f), glm::vec3(0, 1, 0)) * glm::scale(one_mat, glm::vec3(0.1, 0.1, 0.1));

		vkMapMemory(device, DS_picasso_card.uniformBuffersMemory[0][currentImage], 0,
			sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(device, DS_picasso_card.uniformBuffersMemory[0][currentImage]);


		// P I S A R R O //

		ubo.model = one_mat * glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 1.0f, 1.99f));
		ubo.model = ubo.model * glm::rotate(glm::mat4(1.0), glm::radians(180.0f), glm::vec3(0, 1, 0)) * glm::scale(one_mat, glm::vec3(0.4, 0.4, 0.4));

		vkMapMemory(device, DS_pisarro.uniformBuffersMemory[0][currentImage], 0,
			sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(device, DS_pisarro.uniformBuffersMemory[0][currentImage]);

		ubo.model = one_mat * glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 0.35f, 1.99f));
		ubo.model = ubo.model * glm::rotate(glm::mat4(1.0), glm::radians(180.0f), glm::vec3(0, 1, 0)) * glm::scale(one_mat, glm::vec3(0.1, 0.1, 0.1));

		vkMapMemory(device, DS_pisarro_card.uniformBuffersMemory[0][currentImage], 0,
			sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(device, DS_pisarro_card.uniformBuffersMemory[0][currentImage]);


		// S E U R A T //

		ubo.model = one_mat * glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 1.0f, -1.99f));
		ubo.model = ubo.model * glm::rotate(glm::mat4(1.0), glm::radians(0.0f), glm::vec3(0, 1, 0)) * glm::scale(one_mat, glm::vec3(0.4, 0.4, 0.4));

		vkMapMemory(device, DS_seurat.uniformBuffersMemory[0][currentImage], 0,
			sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(device, DS_seurat.uniformBuffersMemory[0][currentImage]);

		ubo.model = one_mat * glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 0.35f, -1.99f));
		ubo.model = ubo.model * glm::rotate(glm::mat4(1.0), glm::radians(0.0f), glm::vec3(0, 1, 0)) * glm::scale(one_mat, glm::vec3(0.1, 0.1, 0.1));

		vkMapMemory(device, DS_seurat_card.uniformBuffersMemory[0][currentImage], 0,
			sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(device, DS_seurat_card.uniformBuffersMemory[0][currentImage]);


		// V A N  G O G H  S T A R R Y //

		ubo.model = one_mat * glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 1.0f, -0.02f));
		ubo.model = ubo.model * glm::rotate(glm::mat4(1.0), glm::radians(180.0f), glm::vec3(0, 1, 0)) * glm::scale(one_mat, glm::vec3(0.4, 0.4, 0.4));

		vkMapMemory(device, DS_vgstar.uniformBuffersMemory[0][currentImage], 0,
			sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(device, DS_vgstar.uniformBuffersMemory[0][currentImage]);

		ubo.model = one_mat * glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.35f, -0.02f));
		ubo.model = ubo.model * glm::rotate(glm::mat4(1.0), glm::radians(180.0f), glm::vec3(0, 1, 0)) * glm::scale(one_mat, glm::vec3(0.1, 0.1, 0.1));

		vkMapMemory(device, DS_vgstar_card.uniformBuffersMemory[0][currentImage], 0,
			sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(device, DS_vgstar_card.uniformBuffersMemory[0][currentImage]);


		// V A N  G O G H  S E L F //

		ubo.model = one_mat * glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, -0.02f));
		ubo.model = ubo.model * glm::rotate(glm::mat4(1.0), glm::radians(180.0f), glm::vec3(0, 1, 0)) * glm::scale(one_mat, glm::vec3(0.18, 0.4, 0.2));

		vkMapMemory(device, DS_vgself.uniformBuffersMemory[0][currentImage], 0,
			sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(device, DS_vgself.uniformBuffersMemory[0][currentImage]);

		ubo.model = one_mat * glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.35f, -0.02f));
		ubo.model = ubo.model * glm::rotate(glm::mat4(1.0), glm::radians(180.0f), glm::vec3(0, 1, 0)) * glm::scale(one_mat, glm::vec3(0.1, 0.1, 0.1));

		vkMapMemory(device, DS_vgself_card.uniformBuffersMemory[0][currentImage], 0,
			sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(device, DS_vgself_card.uniformBuffersMemory[0][currentImage]);


		// C E Z A N N E //

		ubo.model = one_mat * glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 1.0f, 0.1f));
		ubo.model = ubo.model * glm::rotate(glm::mat4(1.0), glm::radians(0.0f), glm::vec3(0, 1, 0)) * glm::scale(one_mat, glm::vec3(0.4, 0.4, 0.4));

		vkMapMemory(device, DS_cezanne.uniformBuffersMemory[0][currentImage], 0,
			sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(device, DS_cezanne.uniformBuffersMemory[0][currentImage]);

		ubo.model = one_mat * glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.35f, 0.1f));
		ubo.model = ubo.model * glm::rotate(glm::mat4(1.0), glm::radians(0.0f), glm::vec3(0, 1, 0)) * glm::scale(one_mat, glm::vec3(0.1, 0.1, 0.1));

		vkMapMemory(device, DS_cezanne_card.uniformBuffersMemory[0][currentImage], 0,
			sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(device, DS_cezanne_card.uniformBuffersMemory[0][currentImage]);


		// V O L P E D O //

		ubo.model = one_mat * glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 0.1f));
		ubo.model = ubo.model * glm::rotate(glm::mat4(1.0), glm::radians(0.0f), glm::vec3(0, 1, 0)) * glm::scale(one_mat, glm::vec3(0.4, 0.4, 0.4));

		vkMapMemory(device, DS_volpedo.uniformBuffersMemory[0][currentImage], 0,
			sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(device, DS_volpedo.uniformBuffersMemory[0][currentImage]);

		ubo.model = one_mat * glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.35f, 0.1f));
		ubo.model = ubo.model * glm::rotate(glm::mat4(1.0), glm::radians(0.0f), glm::vec3(0, 1, 0)) * glm::scale(one_mat, glm::vec3(0.1, 0.1, 0.1));

		vkMapMemory(device, DS_volpedo_card.uniformBuffersMemory[0][currentImage], 0,
			sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(device, DS_volpedo_card.uniformBuffersMemory[0][currentImage]);

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