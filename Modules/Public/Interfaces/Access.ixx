export module AssortX:Access;


namespace AssortX::Access {
	export template <typename T>
	class Handle {
	  private:
		  struct HANDLE_INFO {
			T *Token;
		  } Info = {0};

		public:
		  explicit Handle(T *ID) : Info{.Token = ID} {};
		  [[deprecated("Only meant for internal classes")]]
		  T *GetToken() { return Info.Token; }
		  /*~Handle() {
				  delete Info.Token;
			  }*/
		};
	}
